#include <entities/entities.h>
#include <globals/globals.h>

namespace Entities {
    GetPawn_t getpawn { nullptr };
    GetEntity_t getentity { nullptr };

    void init(SigManager* mgr) {
        getentity = mgr->get<GetEntity_t>("get_player_controller");
        getpawn = mgr->get<GetPawn_t>("get_pawn");
    }

    CBaseEntity* CGameEntitySystem::get_entity(uint32_t index) {
        return getentity(this, index);
    }

    CPlayerPawn* CGameEntitySystem::get_pawn(CPlayerController* player) {
        return getpawn(player);
    }

    uint32_t CGameEntitySystem::get_entity_count() {
        return *reinterpret_cast<uint32_t*>(cast_ptr(this) + Offsets::Client::dwGameEntitySystem_highestEntityIndex);
    }

    EntityType find_type(const char* name) {
        if (strstr(name, "C_Weapon") != nullptr) {
            return EntityType::WEAPON;
        }
        else if (strstr(name, "CCSPlayerController") != nullptr) {
            return EntityType::PLAYER;
        } else {
            return EntityType::BASIC;
        }
    }

    std::vector<std::unique_ptr<Entity>> CGameEntitySystem::get_entities() {
        std::vector<std::unique_ptr<Entity>> entities;
        // starting at 2 so we dont include local player forn now @meatington
        // 01/27/2026 thanks for the heads up xD
        for (uint32_t i{2}; i < this->get_entity_count() * 3; ++i) {
            auto* e =  this->get_entity(i);
            if (e == nullptr) { continue; }

            const auto name { Utility::get_class_name(e) };
            const auto type = find_type(name);

            if (type == EntityType::BASIC) {
                continue;
            }

            entities.push_back(std::make_unique<Entity>(e, type));

        }
        return entities;
    }

    std::vector<CPlayerController*> CGameEntitySystem::get_players() {
        std::vector<CPlayerController*> entities;
        for (uint32_t i{2}; i < 64; ++i) {
            auto* e =  this->get_entity(i);
            if (e == nullptr) { continue; }
            entities.push_back(reinterpret_cast<CPlayerController*>(e));

        }
        return entities;
    }
}
