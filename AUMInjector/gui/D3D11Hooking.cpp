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

#pragma comment(lib, "d3d11.lib")
#include <d3d11.h>
#include <iostream>
#include "D3D11Hooking.hpp"
#include "LoggingSystem.h"

// function pasted from https://stackoverflow.com/a/62240300 with some modifications
bool GetD3D11SwapchainDeviceContext(IDXGISwapChain** pSwapchain, ID3D11Device** pDevice, ID3D11DeviceContext** pContextTable)
{
    WNDCLASSEX wc{ 0 };
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = DefWindowProc;
    wc.lpszClassName = TEXT("dummy class");

    if (!RegisterClassEx(&wc))
    {
        logger.Log(LOG_CODE::ERR, "GUI: Failed to register class");
        return false;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc{ 0 };
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.OutputWindow = GetForegroundWindow();
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel;
    bool success = false;

    for (D3D_DRIVER_TYPE driverType : DRIVER_TYPE_LIST)
    {
        HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, driverType, nullptr, 0, NULL, 0,
            D3D11_SDK_VERSION, &swapChainDesc, pSwapchain, pDevice, &featureLevel, pContextTable);
        if (FAILED(hr))
        {
            logger.LogVariadic(LOG_CODE::INF, false, "Failed to create DeviceAndSwapChain on driver: %d, error code: %d", driverType, hr);
        }
        else
        {
            logger.LogVariadic(LOG_CODE::INF, false, "DeviceAndSwapChain created on driver: %d", driverType);
            success = true;
            break;
        }
    }

    DestroyWindow(swapChainDesc.OutputWindow);
    UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

    if (!success)
    {
        logger.Log(LOG_CODE::ERR, "GUI: Failed to create DeviceAndSwapChain for any driver type");
        return false;
    }
    return true;
}

D3D_PRESENT_FUNCTION GetD3D11PresentFunction()
{
    IDXGISwapChain* swapChain;
    ID3D11Device* device;
    ID3D11DeviceContext* ctx;

    if (GetD3D11SwapchainDeviceContext(&swapChain, &device, &ctx))
    {
        void** vmt = *(void***)swapChain;
        SAFE_RELEASE(swapChain);
        SAFE_RELEASE(device);
        SAFE_RELEASE(ctx);
        return (D3D_PRESENT_FUNCTION)vmt[8];
    }

    return NULL;
}