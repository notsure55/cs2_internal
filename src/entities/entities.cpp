#include <entities/entities.h>
#include <globals/globals.h>

namespace Entities {
    GetPlayer_t getplayer { nullptr };
    GetPawn_t getpawn { nullptr };

    void init(SigManager* mgr) {
        getplayer = mgr->get<GetPlayer_t>("get_player_controller");
        getpawn = mgr->get<GetPawn_t>("get_pawn");
    }

    CPlayerController* CGameEntitySystem::get_player(uint32_t index) {
        return getplayer(this, index);
    }

    CPlayerPawn* CGameEntitySystem::get_pawn(CPlayerController* player) {
        return getpawn(player);
    }

    std::vector<CPlayerController*> CGameEntitySystem::get_entities() {
        std::vector<CPlayerController*> entities;
        // starting at 2 so we dont include local player forn now @meatington
        for (uint32_t i{2}; i < 64; ++i) {
            auto* player =  this->get_player(i);
            if (player != nullptr) {
                entities.push_back(player);
            }
        }
        return entities;
    }
}
