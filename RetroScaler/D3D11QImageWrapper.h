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

#pragma once

#include <QImage>
#include <DirectXTex.h>

class D3D11QImageWrapper
{
public:
	explicit D3D11QImageWrapper(DirectX::ScratchImage && myScratch)
		: scratchImage(std::move(myScratch))
	{
		ConstructQImageFromScratch();
	}
	
	D3D11QImageWrapper() = default;

	/*
	explicit D3D11QImageWrapper(D3D11QImageWrapper&& other)
		: constructedQImage(std::move(other.constructedQImage)),
		scratchImage(std::move(other.scratchImage))
	{
	}
	*/
	const QImage& GetQImage() const
	{
		return constructedQImage;
	}

private:
	QImage constructedQImage;
	DirectX::ScratchImage scratchImage;

	void ConstructQImageFromScratch()
	{
		const uchar* memory{ static_cast<const uchar*>(scratchImage.GetPixels()) };
		constructedQImage = QImage(memory,
			scratchImage.GetMetadata().width,
			scratchImage.GetMetadata().height,
			QImage::Format_ARGB32
		);
	}
};
