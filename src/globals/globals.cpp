#include <globals/globals.h>
#include <sigscanner.h>
#include <utility/utility.h>

namespace Globals {
    Entities::CGameEntitySystem* entity_system { nullptr };
    Inventory::CInventoryManager* inventory_mgr { nullptr };
    Entities::CPlayerController* local_player { nullptr };
    Math::Matrix* view_matrix { nullptr };
    SigManager* mgr { nullptr };
    ImVec2* view_angles { nullptr };

    void setup() {
        mgr = new SigManager;
        mgr->init(Globals::sigs);
        Entities::init(mgr);
        inventory_mgr = Inventory::init(mgr);
        const auto client { cast_ptr(GetModuleHandleW(L"client.dll")) };
        entity_system = mgr->get_class<Entities::CGameEntitySystem>("CGameEntitySystem");
        //local_player = entity_system->get_player(1);
        view_matrix = reinterpret_cast<Math::Matrix*>(client + Offsets::Client::dwViewMatrix);
        view_angles = reinterpret_cast<ImVec2*>(client + Offsets::Client::dwViewAngles);
    }
}
