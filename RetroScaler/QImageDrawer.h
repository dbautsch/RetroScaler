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

#include <QWidget>
#include <QPaintEvent>
#include <QAtomicInt>
#include <QTimer>
#include <QMouseEvent>

#include "ui_QImageDrawer.h"

#include "D3D11QImageWrapper.h"
#include "MouseHandler.h"

class QImageDrawer final : public QWidget
{
	Q_OBJECT

public:
	enum class DrawingPosition
	{
		Center,
		TopLeft
	};

	enum class ScalingMode
	{
		NoScaling,
		PercentValue,
		FitWindow
	};

	enum class ScalingMethod
	{
		NearestNeighbor,
		Bilinear
	};

	explicit QImageDrawer(QWidget *parent = nullptr);
	~QImageDrawer();
	void SetMouseHandler(MouseHandler* handler) { mouseHandler = handler; }

	void SetQImageWrapper(D3D11QImageWrapper imageWrapper);
	void SetDrawingPosition(DrawingPosition position) { drawingPosition = position; }
	void SetScalingMode(ScalingMode mode) { scalingMode = mode; }
	void SetScalingMethod(ScalingMethod method) { scalingMethod = method; }
	void SetScaling(double percentage) { if (scaling > 500 || scaling < 25) { return; } scaling = percentage / 100.0; }

private:
	Ui::QImageDrawerClass ui;
	D3D11QImageWrapper qimageWrapper;
	QAtomicInt drawInProgress;
	QTimer syncTimer;
	DrawingPosition drawingPosition{ DrawingPosition::Center };
	ScalingMode scalingMode{ ScalingMode::NoScaling };
	ScalingMethod scalingMethod{ ScalingMethod::NearestNeighbor };
	double scaling{ 1.0 };
	int xPos{ 0 };
	int yPos{ 0 };
	MouseHandler * mouseHandler{ nullptr };

	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void OnSyncTimer();
};
