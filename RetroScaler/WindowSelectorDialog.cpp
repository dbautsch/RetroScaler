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

	for (size_t index{ 0 }; index < windowEnumerator.GetWindowCount(); ++index)
	{
		const auto& windowTitle{ windowEnumerator.GetSelectedWindowTitle(index) };
		ui.listWidget->addItem(QString::fromStdWString(windowTitle));
	}
}
