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
		const uchar* memory = static_cast<const uchar*>(scratchImage.GetPixels());
		constructedQImage = QImage(memory,
			scratchImage.GetMetadata().width,
			scratchImage.GetMetadata().height,
			QImage::Format_ARGB32
		);
	}
};
