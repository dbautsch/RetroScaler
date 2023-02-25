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
