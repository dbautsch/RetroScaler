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

        directX11WindowCapture->StartCapture(
            windowEnumerator.GetSelectedWindowHandle(selectedWindowIndex));
    }
}

void RetroScaler::OnFrameArrived(D3D11QImageWrapper qimageWrapper)
{
    ui.qimageDrawer->SetQImageWrapper(std::move(qimageWrapper));
}
