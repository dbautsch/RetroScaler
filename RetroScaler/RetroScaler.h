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
