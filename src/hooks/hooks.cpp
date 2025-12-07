#include <hooks/hooks.h>
#include <iostream>
#include <hooks/present/present.h>
#include <print>

namespace Hooks {

    void setup() {

        if (MH_Initialize() != MH_OK) {
            std::println("Failed to init minhook");
            return;
        }

        Present::setup();

        MH_EnableHook(MH_ALL_HOOKS);
    }

    void disable() {
        Present::setlong();
        MH_DisableHook(MH_ALL_HOOKS);
    }
}
