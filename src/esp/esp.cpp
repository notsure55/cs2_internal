#include <esp/esp.h>
#include <globals/globals.h>
#include <offsets/skeletons.h>
#include <entities/entities.h>
#include <utility/utility.h>
#include <cmath>
#include <toggles/toggles.h>
#include <math/math.h>
#include <algorithm>

namespace Esp {

    void testing(Entities::CPlayerPawn* pawn) {
        const auto game_scene { *reinterpret_cast<uintptr_t*>(cast_ptr(pawn) + 0x38) };
        const auto skeletons { *reinterpret_cast<uintptr_t*>(game_scene + 0x290) };
        std::vector<Math::Vec3*> bones;
        bones.reserve(131);
        for (size_t i{0}; i < 123; ++i) {
            bones.push_back(reinterpret_cast<Math::Vec3*>(skeletons + i * 0x20));
        }
        size_t i {0};
        for (const auto bone: bones) {
            ImVec2 screen_coords {};
            if (!Math::wts(bone, screen_coords, nullptr)) {
                continue;
            }

            ImGui::GetBackgroundDrawList()->AddText(
                screen_coords,
                IM_COL32(255, 0, 0, 255),
                std::format("{}", i).c_str()
                );
            i++;
        }
    }

    void skeletons(Entities::CPlayerPawn* pawn) {
        const auto game_scene { *reinterpret_cast<uintptr_t*>(cast_ptr(pawn) + 0x38) };
        const auto skeletons { *reinterpret_cast<uintptr_t*>(game_scene + 0x290) };
        std::vector<Math::Vec3*> bones;
        bones.reserve(array_size(Skeletons::CT::ct_array));
        for (const auto bone: Skeletons::CT::ct_array) {
            bones.push_back(reinterpret_cast<Math::Vec3*>(skeletons + bone * 0x20));
        }
        for (size_t i{0}; i < bones.size() - 1; ++i) {
            ImVec2 bone_1 {};
            ImVec2 bone_2 {};
            if (!Math::wts(bones[i], bone_1, nullptr)) {
                continue;
            }
            if (!Math::wts(bones[i + 1], bone_2, nullptr)) {
                continue;
            }

            ImGui::GetBackgroundDrawList()->AddLine(
                bone_1,
                bone_2,
                IM_COL32(255, 0, 0, 255)
                );
        }
    }

    void boxes(std::unique_ptr<Entities::Entity>& e) {
        const auto pos { e->get_pos() }; // head and feet :P

        ImVec2 head_wts {};
        ImVec2 feet_wts {};

        if (!Math::wts(pos.first, head_wts, nullptr)) {
            return;
        }
        if (!Math::wts(pos.second, feet_wts, nullptr)) {
            return;
        }

        if (e->get_type() == Entities::EntityType::PLAYER) {
            const auto length_scalar { (feet_wts.y - head_wts.y) / 2.0 };
            feet_wts.x -= (length_scalar * 0.4);
            head_wts.x += (length_scalar * 0.4);
            head_wts.y -= (length_scalar * 0.2);
        }

        ImGui::GetBackgroundDrawList()->AddRect(
            head_wts,
            feet_wts,
            IM_COL32(255, 0, 0, 255)
            );
    }

    // MY MATH IS THE GOAT
    void health_bars(Entities::CPlayerPawn* pawn) {
        const auto health { pawn->get_health() };
        const double scale { std::fabsf((100.0 - health) / 100.0) };
        const auto pos { pawn->get_pos() }; // head and feet :P

        ImVec2 head_wts {};
        ImVec2 feet_wts {};

        if (!Math::wts(pos.first, head_wts, nullptr)) {
            return;
        }
        if (!Math::wts(pos.second, feet_wts, nullptr)) {
            return;
        }

        const auto length_scalar { (feet_wts.y - head_wts.y) / 2.0 };
        feet_wts.x -= (length_scalar * 0.52);
        head_wts.x -= (length_scalar * 0.42);
        head_wts.y -= (length_scalar * 0.2) - scale * (length_scalar * 2.2);

        ImGui::GetBackgroundDrawList()->AddRectFilled(
            feet_wts,
            head_wts,
            IM_COL32(255 * scale, 255 / (1.0 - scale) , 0, 255)
        );
    }

    float calc_dist(Math::Vec3* origin, Math::Vec3* target) {
        return (*origin - *target).magnitude();
    }

    void names(std::unique_ptr<Entities::Entity>& e) {
        const auto pos { e->get_pos() };

        ImVec2 feet_wts {};

        if (!Math::wts(pos.second, feet_wts, nullptr)) {
            return;
        }

        ImFont* font = ImGui::GetFont();

        ImGui::GetBackgroundDrawList()->AddText(
            font,
            12.0f,
            feet_wts,
            IM_COL32(0,255,255,255),
            e->get_name()
            );
    }

    void fov() {
        const auto screen_size = Menu::get_screen_size();
        static ImVec2 center = {
            screen_size.x * 0.5f,
            screen_size.y * 0.5f
        };
        ImGui::GetBackgroundDrawList()->AddCircle(
            center,
            Toggles::Aimbot::fov,
            IM_COL32(0, 128, 128, 255)
            );
    }

    void run() {
        if (Toggles::Aimbot::in_fov) {
            fov();
        }

        for (auto& entity: Globals::entity_system->get_entities()) {
            if (entity == nullptr) { continue; }
            auto type = entity->get_type();

            if (!Toggles::Esp::players && type == Entities::EntityType::PLAYER) {
                continue;
            }
            else if (!Toggles::Esp::weapons && type == Entities::EntityType::WEAPON) {
                continue;
            }

            if (type == Entities::EntityType::PLAYER) {
                auto* pawn { Globals::entity_system->get_pawn(entity->get_entity<Entities::CPlayerController>()) };
                const auto health = pawn->get_health();

                if (health > 100 || health <= 0) {
                    continue;
                }

                if (Toggles::Esp::skeletons) {
                    skeletons(pawn);
                }
                if (Toggles::Esp::health) {
                    health_bars(pawn);
                }
            }
            if (Toggles::Esp::boxes) {
                boxes(entity);
            }
            if (Toggles::Esp::names) {
                names(entity);
            }
        }
    }
}
