#include <aimbot/aimbot.h>
#include <globals/globals.h>
#include <offsets/skeletons.h>

namespace Aimbot {
    void run() {
        for (auto* entity: Globals::entity_system->get_entities()) {
            if (entity == nullptr) { continue; }

            auto* pawn { Globals::entity_system->get_pawn(entity) };
            if (pawn->get_health() > 100 || pawn->get_health() <= 0) {
                continue;
            }

            const auto head { pawn->get_bone(Skeletons::CT::BONES::head) };
            const auto local_head { Globals::entity_system->get_pawn(Globals::local_player)->get_bone(Skeletons::CT::BONES::head) };
        }
    }
}
