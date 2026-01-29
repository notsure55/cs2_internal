#pragma once

#include <cstdint>
#include <sigscanner.h>
#include <offsets/offsets.h>
#include <utility/utility.h>
#include <vector>
#include <math/math.h>
#include <offsets/skeletons.h>

namespace Entities {
    enum EntityType {
        PLAYER,
        WEAPON,
        BASIC,
    };

    class CWeapon {
    public:
        char* get_name();
        std::pair<Math::Vec3*, Math::Vec3*> get_pos();
    };

    class CBaseEntity {
    public:
        std::pair<Math::Vec3*, Math::Vec3*> get_pos();
    };

    class Entity {
    private:
        CBaseEntity* entity;
        const EntityType type;

    public:
        Entity(CBaseEntity* e, EntityType t);
        template <typename T>
        T* get_entity() const {
            return reinterpret_cast<T*>(entity);
        }
        const EntityType& get_type() const;
        std::pair<Math::Vec3*, Math::Vec3*> get_pos() const;
        char* get_name() const;
    };

    // CBasePlayerController
    class CPlayerController {
    public:
        char* get_name() const;
    };

    class CPlayerPawn {
    public:
        std::pair<Math::Vec3*, Math::Vec3*> get_pos() const;
        int get_health() const;
        const uintptr_t get_skeleton() const;
        Math::Vec3* get_bone(Skeletons::CT::BONES bone) const;
    };

    class CGameEntitySystem {
    public:

        CPlayerPawn* get_pawn(CPlayerController* player);
        CBaseEntity* get_entity(uint32_t index);
        uint32_t get_entity_count();
        std::vector<CPlayerController*> get_players();
        std::vector<std::unique_ptr<Entity>> get_entities();
    };

    using GetEntity_t = CBaseEntity*(*)(CGameEntitySystem*, uint32_t);
    using GetPawn_t = CPlayerPawn*(*)(void*);

    void init(SigManager* mgr);
}
