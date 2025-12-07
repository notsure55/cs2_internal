#include <Windows.h>
#include <iostream>
#include <print>
#include <sigscanner.h>
#include <globals/globals.h>
#include <entities/entities.h>
#include <utility/utility.h>
#include <hooks/hooks.h>

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
        for (uint32_t i{1}; i < 64; ++i) {
            auto* player =  Globals::entity_system->get_player(i);
            if (player != nullptr) {
                std::println("CONTROLLER: {:X} NAME: {}", cast_ptr(player), player->get_name());
                std::println("PAWN: {:X}", cast_ptr(Globals::entity_system->get_pawn(player)));
            }
        }
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
