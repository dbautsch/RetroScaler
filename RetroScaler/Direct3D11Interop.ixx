/*
* This file is part of RetroScaler.
*
* RetroScaler is free software : you can redistribute itand /or modify it under the terms of
* the GNU General Public License as published by the Free Software Foundation, either version 2
* of the License, or (at your option) any later version.
*
* RetroScaler is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* RetroScaler.If not, see < https://www.gnu.org/licenses/>.
*/

module;

#include <Unknwn.h>
#include <winrt/windows.graphics.directx.direct3d11.h>
#include <inspectable.h>
#include <windows.graphics.directx.direct3d11.interop.h>

#include <d3d11.h>

export module Direct3D11Interop;

export namespace Direct3D11Interop
{
    auto CreateDirect3DDevice(IDXGIDevice* dxgi_device)
    {
        winrt::com_ptr<::IInspectable> d3dDevice;
        winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgi_device, d3dDevice.put()));

        return d3dDevice.as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice>();
    }
    
    template <typename T>
    auto GetDXGIInterfaceFromObject(winrt::Windows::Foundation::IInspectable const& object)
    {
        auto access = object.as<Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess>();
        winrt::com_ptr<T> result;
        winrt::check_hresult(access->GetInterface(winrt::guid_of<T>(), result.put_void()));

        return result;
    }
} // export namespace Direct3D11Interop
