#include <aimbot/aimbot.h>
#include <globals/globals.h>
#include <offsets/skeletons.h>
#include <imgui/imgui.h>
#include <toggles/toggles.h>
#include <utility/utility.h>
#include <cmath>

namespace Aimbot {
    bool in_fov(const ImVec2& angles) {
        auto yaw = std::abs(Globals::view_angles->y - angles.y);
        auto pitch = std::abs(Globals::view_angles->x - angles.x);

        if (yaw > Toggles::Aimbot::fov / 8.0f || pitch > (Toggles::Aimbot::fov / 8.0f)) {
            return false;
        }
        return true;
    }
    void run() {
        ImVec2 closest_angle{};
        float closest_dist { 99999.9f };
        for (auto* entity: Globals::entity_system->get_players()) {
            if (entity == nullptr) { continue; }

            auto* pawn { Globals::entity_system->get_pawn(entity) };
            if (pawn->get_health() > 100 || pawn->get_health() <= 0) {
                continue;
            }

            const auto head { pawn->get_bone(Skeletons::CT::BONES::head) };
            const auto local_head { Globals::entity_system->get_pawn(Globals::local_player)->get_bone(Skeletons::CT::BONES::head) };
            const auto angles { calculate_angle(local_head, head) };

            if (!in_fov(angles) && Toggles::Aimbot::in_fov) {
                continue;
            }

            auto dist { (angles.x * angles.x) + (angles.y * angles.y) };

            if (closest_dist >= dist) {
                closest_dist = dist;
                closest_angle = angles;
            }
        }

        if (closest_dist != 99999.9f) {
            *Globals::view_angles = closest_angle;
        }
    }
}
