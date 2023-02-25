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

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QGraphicsView>

#include "ui_RetroScaler.h"
#include "D3D11QImageWrapper.h"

#include <memory>

import Direct3D11;
import DirectX11WindowCapture;
import WindowEnumerator;

class RetroScaler : public QMainWindow
{
    Q_OBJECT

public:
    RetroScaler(QWidget *parent = nullptr);
    ~RetroScaler();

private:
    Ui::RetroScalerClass ui;
    std::unique_ptr<Direct3D11> direct3d11;
    std::unique_ptr<DirectX11WindowCapture> directX11WindowCapture;
    int selectedWindowIndex{ -1 };
    WindowEnumerator windowEnumerator;
    QTimer windowSelectorTimer;


    void OnFrameArrived(D3D11QImageWrapper qimageWrapper);

private slots:
    void OnWindowSelectorTimer();
};
