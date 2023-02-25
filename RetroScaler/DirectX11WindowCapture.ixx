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
#include <winrt/Windows.Graphics.Capture.h>

#include <windows.graphics.capture.interop.h>

#include <inspectable.h>
#include <wincodec.h>

#include "D3D11QImageWrapper.h"

#include <DirectXTex.h>

#include <functional>

export module DirectX11WindowCapture;

import Direct3D11Interop;

export class DirectX11WindowCapture
{
public:
	using OnFrameArrived = std::function<void(D3D11QImageWrapper)>;

	explicit DirectX11WindowCapture(OnFrameArrived onFrameArrivedCallback,
		winrt::com_ptr<ID3D11Device> device);
	~DirectX11WindowCapture();
	
	void StartCapture(HWND hwnd);
	void StopCapture();

private:
	OnFrameArrived onFrameArrived;
	winrt::com_ptr<ID3D11Device> d3d11Device{ nullptr };
	HWND windowToCapture{ nullptr };
	winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool framesPool{ nullptr };
	winrt::Windows::Graphics::Capture::GraphicsCaptureSession captureSession{ nullptr };
	winrt::Windows::Graphics::Capture::GraphicsCaptureItem captureItem{ nullptr };

	void OnNewFrameCaptured(winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool
		const& sender, winrt::Windows::Foundation::IInspectable const&);
};

DirectX11WindowCapture::DirectX11WindowCapture(
	OnFrameArrived onFrameArrivedCallback, winrt::com_ptr<ID3D11Device> device)
	:
	onFrameArrived(onFrameArrivedCallback),
	d3d11Device(device)
{
}

DirectX11WindowCapture::~DirectX11WindowCapture()
{
	StopCapture();
}

void DirectX11WindowCapture::StartCapture(HWND hwnd)
{
	windowToCapture = hwnd;

	auto interopFactory{ winrt::get_activation_factory<winrt::Windows::Graphics::Capture::GraphicsCaptureItem, IGraphicsCaptureItemInterop>() };
	
	winrt::check_hresult(interopFactory->CreateForWindow(windowToCapture,
		winrt::guid_of<ABI::Windows::Graphics::Capture::IGraphicsCaptureItem>(), winrt::put_abi(captureItem)));

	const auto myPixelFormat{ winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized };
	const auto myDXGIDevice{ d3d11Device.as<IDXGIDevice>() };
	const auto myDevice { Direct3D11Interop::CreateDirect3DDevice(myDXGIDevice.get()) };
	
	framesPool = winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool::CreateFreeThreaded(
		myDevice, myPixelFormat, 2, captureItem.Size()
	);
	framesPool.FrameArrived({ this, &DirectX11WindowCapture::OnNewFrameCaptured });
	captureSession = framesPool.CreateCaptureSession(captureItem);
	captureSession.StartCapture();
}

void DirectX11WindowCapture::OnNewFrameCaptured(
	winrt::Windows::Graphics::Capture::Direct3D11CaptureFramePool const & sender,
	winrt::Windows::Foundation::IInspectable const&)
{
	auto frame{ sender.TryGetNextFrame() };
	auto texture{ Direct3D11Interop::GetDXGIInterfaceFromObject<ID3D11Texture2D>(frame.Surface()) };

	winrt::com_ptr<ID3D11DeviceContext> immediateContext{ nullptr };
	d3d11Device->GetImmediateContext(immediateContext.put());

	D3D11_TEXTURE2D_DESC desc {};
	winrt::com_ptr<ID3D11Texture2D> pStaging;
	DirectX::ScratchImage image;
	HRESULT hr{ DirectX::CaptureTexture(d3d11Device.get(), immediateContext.get(),
		texture.get(), image) };

	if (FAILED(hr))
	{
		throw std::runtime_error("unable to capture texture");
	}

	D3D11QImageWrapper qimageWrapper(std::move(image));

	if (onFrameArrived != nullptr)
	{
		onFrameArrived(std::move(qimageWrapper));
	}
}

void DirectX11WindowCapture::StopCapture()
{
	onFrameArrived = nullptr;

	if (captureSession != nullptr)
	{
		captureSession.Close();
		captureSession = nullptr;
	}

	if (framesPool != nullptr)
	{
		framesPool.Close();
		framesPool = nullptr;
	}
}
