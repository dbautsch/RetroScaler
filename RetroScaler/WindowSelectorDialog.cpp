#include "WindowSelectorDialog.h"

#include <ranges>

#include <QString>

WindowSelectorDialog::WindowSelectorDialog(
	WindowEnumerator & theWindowEnumerator,
	QWidget *parent)
	: 
	QDialog(parent),
	windowEnumerator(theWindowEnumerator)
{
	ui.setupUi(this);

	connect(ui.pushButton,
		&QPushButton::clicked,
		this, &WindowSelectorDialog::OnSelect);

	connect(ui.pushButton_2,
		&QPushButton::clicked,
		this, &WindowSelectorDialog::OnRefresh);
}

WindowSelectorDialog::~WindowSelectorDialog()
{}

void WindowSelectorDialog::showEvent(QShowEvent*)
{
	OnRefresh();
}

void WindowSelectorDialog::OnSelect()
{
	if (ui.listWidget->selectedItems().empty())
	{
		return;
	}

	selectedWindowIndex = ui.listWidget->currentRow();
	accept();
}

void WindowSelectorDialog::OnRefresh()
{
	windowEnumerator.RefreshList();
	ui.listWidget->clear();

	for (size_t index = 0; index < windowEnumerator.GetWindowCount(); ++index)
	{
		const auto& windowTitle = windowEnumerator.GetSelectedWindowTitle(index);
		ui.listWidget->addItem(QString::fromStdWString(windowTitle));
	}
}
