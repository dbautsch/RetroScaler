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

#include <d3d11.h>

#include <winrt/Windows.Foundation.h>

export module Direct3D11;

export class Direct3D11
{
public:
	Direct3D11();
	winrt::com_ptr<ID3D11Device> Device() const { return d3d11Device; }


private:
	winrt::com_ptr<ID3D11Device> d3d11Device{ nullptr };

	winrt::com_ptr<ID3D11Device> CreateD3D11Device();
};

Direct3D11::Direct3D11()
{
	d3d11Device = CreateD3D11Device();
}

winrt::com_ptr<ID3D11Device> Direct3D11::CreateD3D11Device()
{
	winrt::com_ptr<ID3D11Device> device;
	UINT flags{ D3D11_CREATE_DEVICE_BGRA_SUPPORT };

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	const auto deviceType{ D3D_DRIVER_TYPE_HARDWARE };
	const HRESULT d3dResult{ D3D11CreateDevice(
		nullptr,
		deviceType,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		device.put(),
		nullptr, nullptr
	) };
	winrt::check_hresult(d3dResult);

	return device;
}
