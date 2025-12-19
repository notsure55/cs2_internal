#pragma once

#include <cstdint>
#include <sigscanner.h>
#include <offsets/offsets.h>
#include <utility/utility.h>
#include <vector>
#include <math/math.h>
#include <offsets/skeletons.h>

namespace Entities {
    // CBasePlayerController
    class CPlayerController {
    public:
        char* get_name() {
            return reinterpret_cast<char*>(cast_ptr(this) + Offsets::Client::CBasePlayerController::m_iszPlayerName);
        }
    };

    class CPlayerPawn {
    public:
        std::pair<Math::Vec3*, Math::Vec3*> get_pos() {
            return { reinterpret_cast<Math::Vec3*>(cast_ptr(this) + Offsets::Client::C_CSPlayerPawn::m_vecLastClipCameraPos), reinterpret_cast<Math::Vec3*>(cast_ptr(this) + Offsets::Client::C_BasePlayerPawn::m_vOldOrigin) };
        }

        int get_health() {
            return *reinterpret_cast<int*>(cast_ptr(this) + Offsets::Client::C_BaseEntity::m_iHealth);
        }

        const uintptr_t get_skeleton() {
            const auto game_scene { *reinterpret_cast<uintptr_t*>(cast_ptr(this) + 0x38) };
            const auto skeletons { *reinterpret_cast<uintptr_t*>(game_scene + 0x290) };
            return skeletons;
        }

        Math::Vec3* get_bone(Skeletons::CT::BONES bone) {
            return reinterpret_cast<Math::Vec3*>(this->get_skeleton() + bone * 0x20);
        }
    };

    class CBaseEntity {
    };

    class CGameEntitySystem {
    public:

        CPlayerController* get_player(uint32_t index);
        CPlayerPawn* get_pawn(CPlayerController* player);
        CBaseEntity* get_entity(uint32_t index);
        uint32_t get_entity_count();
        std::vector<CPlayerController*> get_entities();
    };

    using GetPlayer_t = CPlayerController*(*)(CGameEntitySystem*, uint32_t);
    using GetPawn_t = CPlayerPawn*(*)(void*);

    void init(SigManager* mgr);
}
