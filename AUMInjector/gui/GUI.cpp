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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d11.h>
#include <detours.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include "D3D11Hooking.hpp"
#include "GUI.h"

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

LRESULT CALLBACK WndProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
    POINT mPos;

    GetCursorPos(&mPos);
    ScreenToClient(window, &mPos);
    ImGui::GetIO().MousePos.x = mPos.x;
    ImGui::GetIO().MousePos.y = mPos.y;

    if (uMsg == WM_KEYUP && wParam == VK_DELETE) guiShowMenu = !guiShowMenu;
    if (guiShowMenu)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        if (io.WantCaptureMouse || io.WantCaptureKeyboard) return TRUE;
    }

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
        ImGui::StyleColorsDark();
        window = desc.OutputWindow;

        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(Device, Ctx);

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        OriginalWndProcFunction = (WNDPROC)SetWindowLongW(window, GWLP_WNDPROC, (LONG)WndProcHook);
        ImGui::GetIO().ImeWindowHandle = window;

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
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if (guiShowMenu)
    {
        ImGui::ShowDemoWindow();
    }
    ImGui::EndFrame();
    ImGui::Render();

    Ctx->OMSetRenderTargets(1, &RenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return OriginalD3DFunction(pThis, SyncInterval, Flags);
}

void GUIDetourAttach()
{
    OriginalD3DFunction = GetD3D11PresentFunction();
    DetourAttach(&(PVOID&)OriginalD3DFunction, D3D_FUNCTION_HOOK);
}
