#include <menu/menu.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>
#include <hooks/present/present.h>
#include <hooks/hooks.h>
#include <esp/esp.h>
#include <toggles/toggles.h>

namespace Menu {
    void menu() {
        ImGui::Begin("Black");
        if (ImGui::BeginTabBar("Modules")) {
            if (ImGui::BeginTabItem("Esp")) {
                ImGui::Checkbox("Boxes", &Toggles::Esp::boxes);
                ImGui::Checkbox("Skeletons", &Toggles::Esp::skeletons);
                ImGui::Checkbox("Health", &Toggles::Esp::health);
                ImGui::Checkbox("Names", &Toggles::Esp::names);
                ImGui::Checkbox("Players" , &Toggles::Esp::players);
                ImGui::Checkbox("Weapons" , &Toggles::Esp::weapons);
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
