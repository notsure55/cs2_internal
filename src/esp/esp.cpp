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
            if (!Math::wts(bone, screen_coords)) {
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
            if (!Math::wts(bones[i], bone_1)) {
                continue;
            }
            if (!Math::wts(bones[i + 1], bone_2)) {
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

        if (!Math::wts(pos.first, head_wts)) {
            return;
        }
        if (!Math::wts(pos.second, feet_wts)) {
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

        if (!Math::wts(pos.first, head_wts)) {
            return;
        }
        if (!Math::wts(pos.second, feet_wts)) {
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
        const auto local_player_pos { Globals::entity_system->get_pawn(Globals::local_player)->get_pos().first };
        const float dist { calc_dist(local_player_pos, pos.first)};
        //std::println("LOCAL_PLAYER_POS: X: {} Y: {} Z: {}", local_player_pos->x, local_player_pos->y, local_player_pos->z);

        ImVec2 head_wts {};
        ImVec2 feet_wts {};

        if (!Math::wts(pos.first, head_wts)) {
            return;
        }
        if (!Math::wts(pos.second, feet_wts)) {
            return;
        }
        if (e->get_type() == Entities::EntityType::PLAYER) {
            const auto length_scalar { (feet_wts.y - head_wts.y) / 2.0f };
            head_wts.x -= (length_scalar * 0.42f);
            head_wts.y -= (length_scalar * 0.3f);
        }

        ImFont* font = ImGui::GetFont();
        float font_size = std::clamp(24.0f - dist / 100.0f, 6.0f, 24.0f);

        ImGui::GetBackgroundDrawList()->AddText(
            font,
            font_size,
            head_wts,
            IM_COL32(0,255,255,255),
            e->get_name()
            );
    }

    void run() {
        for (auto& entity: Globals::entity_system->get_entities()) {
            if (entity == nullptr) { continue; }

            if (entity->get_type() == Entities::EntityType::PLAYER) {
                auto* pawn { Globals::entity_system->get_pawn(entity->get_entity<Entities::CPlayerController>()) };

                if (pawn->get_health() > 100 || pawn->get_health() <= 0) {
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
