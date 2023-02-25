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
	QPainter painter(this);
	painter.drawImage(QPoint(0, 0), qimageWrapper.GetQImage());
	painter.end();
	drawInProgress = 0;
}

void QImageDrawer::OnSyncTimer()
{
	this->update();
}
