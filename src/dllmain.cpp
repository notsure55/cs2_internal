#include <Windows.h>
#include <iostream>
#include <print>
#include <sigscanner.h>
#include <globals/globals.h>
#include <entities/entities.h>
#include <utility/utility.h>
#include <hooks/hooks.h>
#include <aimbot/aimbot.h>

DWORD WINAPI entry_point(LPVOID hModule) {
    if (!AllocConsole()) {
        return 1;
    }

    FILE* f{ nullptr };
    freopen_s(&f, "CONOUT$", "w", stdout);

    Globals::setup();
    Hooks::setup();

    while (true) {
        if (GetAsyncKeyState(VK_DELETE)) {
            break;
        }
        if (GetAsyncKeyState(VK_XBUTTON2)) {
            /*for (const auto& item: Globals::inventory_mgr->get_player_inv()->get_items()) {
                //std::println("ADDRESS: {:X} NAME: INVALID", cast_ptr(item));
                const auto name { item->get_name() };
                if (name != nullptr) {
                    std::println("ADDRESS: {:X} NAME: {}", cast_ptr(item), item->get_name());
                } else {
                    std::println("ADDRESS: {:X} NAME: INVALID", cast_ptr(item));
                }
            }*/

            Aimbot::run();
        }

        std::println("INVENTORY: {:X} PLAYER_INVENTORY: {:X}", cast_ptr(Globals::inventory_mgr), cast_ptr(Globals::inventory_mgr->get_player_inv()));
        auto inv { Globals::inventory_mgr->get_player_inv()->get_items() };

        for (int i{0}; i < inv.count; ++i) {
            std::println("ADDRESS: {:X} NAME: {}", cast_ptr(inv.items[i]), inv.items[i]->get_name());
        }
        /*for (uint32_t i{1}; i < 64; ++i) {
            auto* player =  Globals::entity_system->get_player(i);
            if (player != nullptr) {
                std::println("CONTROLLER: {:X} NAME: {}", cast_ptr(player), player->get_name());
                std::println("PAWN: {:X}", cast_ptr(Globals::entity_system->get_pawn(player)));
            }

        }*/
        Sleep(1000);
    }

    Hooks::disable();

    if (f) {
        fclose(f);
    }

    FreeConsole();
    FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH: {
        const auto handle{ CreateThread(nullptr, NULL, entry_point, static_cast<LPVOID>(hModule), NULL, NULL) };

        if (handle) {
            CloseHandle(handle);
        }
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
