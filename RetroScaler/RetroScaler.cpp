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

#include "RetroScaler.h"

#include "WindowSelectorDialog.h"

RetroScaler::RetroScaler(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    windowSelectorTimer.setInterval(100);
    connect(&windowSelectorTimer, &QTimer::timeout,
        this, &RetroScaler::OnWindowSelectorTimer);
    windowSelectorTimer.setSingleShot(true);
    windowSelectorTimer.start();
}

RetroScaler::~RetroScaler()
{
    if (directX11WindowCapture != nullptr)
    {
        directX11WindowCapture->StopCapture();
    }
}

void RetroScaler::OnWindowSelectorTimer()
{
    direct3d11.reset(new Direct3D11());
    directX11WindowCapture.reset(
        new DirectX11WindowCapture(std::bind(&RetroScaler::OnFrameArrived, this, std::placeholders::_1),
            direct3d11->Device())
    );

    WindowSelectorDialog windowSelectorDialog(windowEnumerator, this);
    windowSelectorDialog.exec();

    if (windowSelectorDialog.result() == QDialog::Accepted)
    {
        selectedWindowIndex = windowSelectorDialog.GetSelectedWindowIndex();
        const auto targetWindow{ windowEnumerator.GetSelectedWindowHandle(selectedWindowIndex) };
        mouseHandler.reset(new MouseHandler(targetWindow));
        ui.qimageDrawer->SetMouseHandler(mouseHandler.get());
        directX11WindowCapture->StartCapture(targetWindow);
    }
}

void RetroScaler::OnFrameArrived(D3D11QImageWrapper qimageWrapper)
{
    ui.qimageDrawer->SetQImageWrapper(std::move(qimageWrapper));
}
