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

#include <QDialog>
#include "ui_WindowSelectorDialog.h"

#include <QShowEvent>

import WindowEnumerator;

class WindowSelectorDialog : public QDialog
{
	Q_OBJECT

public:
	WindowSelectorDialog(
		WindowEnumerator & theWindowEnumerator,
		QWidget *parent = nullptr);
	~WindowSelectorDialog();
	int GetSelectedWindowIndex() const { return selectedWindowIndex; }

private slots:
	void OnSelect();
	void OnRefresh();

private:
	WindowEnumerator& windowEnumerator;
	Ui::WindowSelectorDialogClass ui;
	int selectedWindowIndex{ -1 };

	void showEvent(QShowEvent*) override;
};
