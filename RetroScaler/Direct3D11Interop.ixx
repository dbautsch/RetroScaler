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

    auto CreateDirect3DSurface(IDXGISurface* dxgiSurface)
    {
        winrt::com_ptr<::IInspectable> d3d_surface;
        winrt::check_hresult(CreateDirect3D11SurfaceFromDXGISurface(dxgiSurface, d3d_surface.put()));

        return d3d_surface.as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface>();
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
