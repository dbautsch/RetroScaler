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

#include "QImageDrawer.h"

#include <QPainter>

static constexpr int redrawFps{ 60 };
static constexpr int redrawMs{ 1000 / redrawFps };

QImageDrawer::QImageDrawer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	syncTimer.setSingleShot(false);
	syncTimer.setInterval(redrawMs);
	connect(&syncTimer, &QTimer::timeout, this, &QImageDrawer::OnSyncTimer);
	syncTimer.start();
}

QImageDrawer::~QImageDrawer()
{}

void QImageDrawer::SetQImageWrapper(D3D11QImageWrapper imageWrapper)
{
	if (drawInProgress == 0)
	{
		qimageWrapper = std::move(imageWrapper);
	}
}

void QImageDrawer::paintEvent(QPaintEvent* event)
{
	if (qimageWrapper.GetQImage().isNull()) [[unlikely]]
	{
		return;
	}

	drawInProgress = 1;

	int centerX{ 0 };
	int centerY{ 0 };
	int targetWidth{ qimageWrapper.GetWidth() };
	int targetHeight{ qimageWrapper.GetHeight() };
	const QRect clientRect = this->contentsRect();
	int x{ 0 };
	int y{ 0 };

	if (drawingPosition == DrawingPosition::Center) [[likely]]
	{
		centerX = clientRect.width() / 2.0;
		centerY = clientRect.height() / 2.0;
	}

	if (scalingMode == ScalingMode::PercentValue) [[likely]]
	{
		targetHeight *= scaling;
		targetWidth *= scaling;
	}
	else if (scalingMode == ScalingMode::FitWindow)
	{
		if (targetWidth > clientRect.width())
		{
			double ratio{ static_cast<double>(targetWidth) / static_cast<double>(targetHeight) };
			targetWidth = clientRect.height();
			targetHeight = targetWidth * ratio;
		}

		if (targetHeight > clientRect.height())
		{
			double ratio{ static_cast<double>(targetHeight) / static_cast<double>(targetWidth) };
			targetHeight = clientRect.height();
			targetWidth = targetHeight * ratio;
		}
	}

	QPainter painter(this);
	const auto brush{ Qt::black };
	painter.fillRect(clientRect, brush);
	auto device{ painter.device() };
	const auto ratio{ 1.0 / device->devicePixelRatioF() };
	const QSize targetSize{ static_cast<int>(targetWidth * ratio), static_cast<int>(targetHeight * ratio) };
	const auto left{ centerX - ((targetWidth / 2.0) * ratio) };
	const auto top{ centerY - ((targetHeight / 2.0) * ratio) };
	const QPoint targetPos{ static_cast<int>(left), static_cast<int>(top) };
	painter.drawImage(QRect(targetPos, targetSize), qimageWrapper.GetQImage());
	painter.end();

	drawInProgress = 0;

	xPos = targetPos.x();
	yPos = targetPos.y();
}

void QImageDrawer::OnSyncTimer()
{
	this->update();
}

void QImageDrawer::mousePressEvent(QMouseEvent* event)
{
	if (mouseHandler == nullptr)
	{
		return;
	}

	mouseHandler->SimulateClick(100, 100, MouseHandler::MouseButton::Left);
}
