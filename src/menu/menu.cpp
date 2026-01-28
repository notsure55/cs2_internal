#include <menu/menu.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>
#include <hooks/present/present.h>
#include <hooks/hooks.h>
#include <esp/esp.h>
#include <toggles/toggles.h>
#include <iostream>

namespace Menu {
    const char* esp_combo[] = { "Players", "Weapons" };
    static const char* current_selection = "Players";

    void menu() {
        ImGui::Begin("Black");
        if (ImGui::BeginTabBar("Modules")) {
            if (ImGui::BeginTabItem("Esp")) {
                if (ImGui::BeginCombo("##combo", current_selection)) {
                    for (int n = 0; n < IM_ARRAYSIZE(esp_combo); n++) {
                        bool is_selected = (current_selection == esp_combo[n]);
                        if (ImGui::Selectable(esp_combo[n], is_selected)) {
                            current_selection = esp_combo[n];
                        }
                        if (is_selected) {
                            ImGui::SetItemDefaultFocus(); // Set initial focus
                        }
                    }
                    ImGui::EndCombo();
                }
                if (std::strcmp(current_selection, "Players") == 0) {
                    ImGui::Checkbox("Toggle" , &Toggles::Esp::players);
                    ImGui::Checkbox("Boxes", &Toggles::Esp::Players::boxes);
                    ImGui::Checkbox("Names", &Toggles::Esp::Players::names);
                    ImGui::Checkbox("Skeletons", &Toggles::Esp::Players::skeletons);
                    ImGui::Checkbox("Health", &Toggles::Esp::Players::health);
                } else {
                    ImGui::Checkbox("Toggle" , &Toggles::Esp::weapons);
                    ImGui::Checkbox("Boxes", &Toggles::Esp::Weapons::boxes);
                    ImGui::Checkbox("Names", &Toggles::Esp::Weapons::names);
                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Aimbot")) {
                ImGui::Checkbox("FOV", &Toggles::Aimbot::in_fov);
                ImGui::SliderFloat("Slider", &Toggles::Aimbot::fov, 0.0f, 180.f);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    ImVec2 get_screen_size() {
        return ImGui::GetIO().DisplaySize;
    }

    void render(ID3D11DeviceContext* context, ID3D11RenderTargetView* mainRenderTargetView) {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (Present::menu) {
            menu();
        }

        Esp::run();

        ImGui::Render();
        context->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}
