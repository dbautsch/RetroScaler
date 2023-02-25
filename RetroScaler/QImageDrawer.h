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

#include "ui_QImageDrawer.h"

#include "D3D11QImageWrapper.h"

class QImageDrawer : public QWidget
{
	Q_OBJECT

public:
	QImageDrawer(QWidget *parent = nullptr);
	~QImageDrawer();

	void SetQImageWrapper(D3D11QImageWrapper imageWrapper);

private:
	Ui::QImageDrawerClass ui;
	D3D11QImageWrapper qimageWrapper;
	QAtomicInt drawInProgress;
	QTimer syncTimer;

	void paintEvent(QPaintEvent* event) override;
	void OnSyncTimer();
};
