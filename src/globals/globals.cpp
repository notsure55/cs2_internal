#include <globals/globals.h>
#include <sigscanner.h>
#include <utility/utility.h>

namespace Globals {
    Entities::CGameEntitySystem* entity_system { nullptr };
    Entities::CPlayerController* local_player { nullptr };
    Math::Matrix* view_matrix { nullptr };
    SigManager* mgr { nullptr };

    void setup() {
        mgr = new SigManager;
        mgr->init(Globals::sigs);
        Entities::init(mgr);
        const auto client { cast_ptr(GetModuleHandleW(L"client.dll")) };
        entity_system = mgr->get_class<Entities::CGameEntitySystem>("CGameEntitySystem");
        local_player = entity_system->get_player(1);
        view_matrix = reinterpret_cast<Math::Matrix*>(client + Offsets::Client::dwViewMatrix);
    }
}
