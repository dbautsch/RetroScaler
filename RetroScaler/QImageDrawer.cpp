#include "QImageDrawer.h"

#include <QPainter>

static constexpr int redrawFps = 60;
static constexpr int redrawMs = 1000 / redrawFps;

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
