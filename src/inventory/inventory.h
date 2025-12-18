#pragma once

#include <sigscanner.h>

namespace Inventory {
    class C_EconItemView {
    public:
        char* get_name();
    };

    struct Inventory {
        C_EconItemView** items;
        int count;
    };

    class CPlayerInventory {
    public:
        Inventory get_items();
    };

    class CInventoryManager {
    public:
        CPlayerInventory* get_player_inv();
    };

    using get_inventory_t = CInventoryManager*(*)();
    CInventoryManager* init(SigManager* mgr);
}
