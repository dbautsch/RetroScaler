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
