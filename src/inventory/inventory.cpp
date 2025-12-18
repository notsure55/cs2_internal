#include <inventory/inventory.h>
#include <utility/utility.h>

namespace Inventory {
    CInventoryManager* init(SigManager* mgr) {
        return mgr->get<get_inventory_t>("get_inventory")();
    }

    CPlayerInventory* CInventoryManager::get_player_inv() {
        return *reinterpret_cast<CPlayerInventory**>(cast_ptr(this) + 0x3FC60);
    }

    Inventory CPlayerInventory::get_items() {
        const auto items { *reinterpret_cast<C_EconItemView***>(cast_ptr(this) + 0x28) };

        const Inventory inv {
            .items = items,
            .count = *reinterpret_cast<int*>(cast_ptr(this) + 0x20),
        };

        return inv;
    }


    char* C_EconItemView::get_name() {
        const auto desc { *reinterpret_cast<uintptr_t*>(cast_ptr(this) + 0x200) };
        return *reinterpret_cast<char**>(*reinterpret_cast<uintptr_t*>(desc + 0x10) + 0x8);
    }

}
