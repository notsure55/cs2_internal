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
            Aimbot::run();
        }

        for (uint32_t i{0}; i < Globals::entity_system->get_entity_count() * 3; ++i) {
            auto* entity =  Globals::entity_system->get_player(i);
            if (entity != nullptr) {
                const auto name { Utility::get_class_name(entity) };
                if (std::strcmp("C_BaseModelEntity@@", name) != 0) {
                    std::println("Entity: {:X}, Class Name: {}", cast_ptr(entity), name);
                }
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
