#pragma once

#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include <imgui/imgui.h>
#include <vector>

namespace Menu {
    void render(ID3D11DeviceContext* context, ID3D11RenderTargetView* mainRenderTargetView);
    ImVec2 get_screen_size();
    void destroy();
}
