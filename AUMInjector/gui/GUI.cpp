// Original source: https://github.com/ExtraConcentratedJuice/ChristWareAmongUs
//
//MIT License
//
//Copyright(c) ExtraConcentratedJuice
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "D3D11Hooking.hpp"
#include "MumblePlayer.h"
#include "settings.h"
#include "GUI.h"
#include "GUIWindow.h"
#include "Blocks/PlayerInfoBlock.h"
#include "Blocks/PositionRadarBlock.h"
#include "Blocks/SettingsBlock.h"
#include "Blocks/OverlayBlock.h"
#include "Blocks/AboutBlock.h"
#include "Input.h"

IDXGISwapChain* SwapChain;
ID3D11Device* Device;
ID3D11DeviceContext* Ctx;
ID3D11RenderTargetView* RenderTargetView;

D3D_PRESENT_FUNCTION OriginalD3DFunction;
WNDPROC OriginalWndProcFunction;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool guiShowMenu = false;
bool guiInitialized = false;
HWND window;

std::vector<GUIWindow*> GUIWindows;
GUIWindow* overlayWindow;

LRESULT CALLBACK WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
    POINT mPos;

    GetCursorPos(&mPos);
    ScreenToClient(window, &mPos);
    ImGui::GetIO().MousePos.x = (float)mPos.x;
    ImGui::GetIO().MousePos.y = (float)mPos.y;

    if (uMsg == WM_KEYUP && wParam == VK_DELETE) guiShowMenu = !guiShowMenu;

    // Set the alphabet when it comes in.
    if (uMsg == WM_KEYUP && wParam >= 'A' && wParam <= 'Z')
    {
        inputSingleton.SetKey(wParam, false);
    }
    else if (uMsg == WM_KEYDOWN && wParam >= 'A' && wParam <= 'Z')
    {
        inputSingleton.SetKey(wParam, true);
    }

    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
    if (io.WantCaptureMouse && 
        (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_MOUSEMOVE)) return TRUE;

    return CallWindowProcW(OriginalWndProcFunction, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall D3D_FUNCTION_HOOK(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags)
{
    if (!guiInitialized)
    {
        SwapChain = pThis;
        pThis->GetDevice(__uuidof(ID3D11Device), (void**)&Device);
        Device->GetImmediateContext(&Ctx);

        DXGI_SWAP_CHAIN_DESC desc;
        pThis->GetDesc(&desc);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_Button] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
        colors[ImGuiCol_Header] = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 0.54f);
        colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
        colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);

        window = desc.OutputWindow;

        io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard |
            ImGuiConfigFlags_DockingEnable;

        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(Device, Ctx);

        //io.ConfigViewportsNoAutoMerge = true;
        OriginalWndProcFunction = (WNDPROC)SetWindowLongW(window, GWLP_WNDPROC, (LONG)WndProcHook);
        // ImGui::GetIO().ImeWindowHandle = window;

        ID3D11Texture2D* pBackBuffer;
        pThis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
        Device->CreateRenderTargetView(pBackBuffer, NULL, &RenderTargetView);
        pBackBuffer->Release();

        ImGui::GetStyle().WindowRounding = 0.0F;
        ImGui::GetStyle().ChildRounding = 0.0F;
        ImGui::GetStyle().FrameRounding = 0.0F;
        ImGui::GetStyle().GrabRounding = 0.0F;
        ImGui::GetStyle().PopupRounding = 0.0F;
        ImGui::GetStyle().ScrollbarRounding = 0.0F;
        guiInitialized = true;

        // Add windows
        GUIWindow* window1 = new GUIWindow("About", 0);
        window1->AddBlock(new AboutBlock());
        GUIWindows.emplace_back(window1);

        GUIWindow* window0 = new GUIWindow("Player Info", 0);
        window0->AddBlock(new PlayerInfoBlock());
        GUIWindows.emplace_back(window0);

        GUIWindow* window2 = new GUIWindow("Proximity Configuration", 0);
        window2->AddBlock(new SettingsBlock());
        GUIWindows.emplace_back(window2);

#ifdef DEV_TOOLS
		GUIWindow* window3 = new GUIWindow("Positional Radar", 0);
        window3->AddBlock(new PositionRadarBlock());
        GUIWindows.emplace_back(window3);
#endif


        overlayWindow = new GUIWindow("Overlay", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove);
        overlayWindow->AddBlock(new OverlayBlock(&guiShowMenu));
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Render menu
    if (guiShowMenu)
    {
        for (GUIWindow* window : GUIWindows)  window->Update();
    }

    if (!appSettings.disableOverlay)
    {
        // Render overlay
        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2.0f, 10.0f),
            ImGuiCond_Always, ImVec2(0.5f, 0.0f));
        ImGui::SetNextWindowBgAlpha(0.5f);
        overlayWindow->Update();
    }

    ImGui::Render();
    ImGui::EndFrame(); 

    Ctx->OMSetRenderTargets(1, &RenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return OriginalD3DFunction(pThis, SyncInterval, Flags);
}

void GUIDetourAttach()
{
    // Don't need to free GUIWindows' blocks, the windows free them

    OriginalD3DFunction = GetD3D11PresentFunction();
    DetourAttach(&(PVOID&)OriginalD3DFunction, D3D_FUNCTION_HOOK);
}
