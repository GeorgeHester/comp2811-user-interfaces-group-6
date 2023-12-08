#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QComboBox>

#include "header.h"
#include "settingshandler.h"
#include "displaymode.h"
#include "rootwindow.h"

class SettingsWindow : public QWidget
{
    Q_OBJECT

  public:
    SettingsWindow();

    QComboBox* display_mode_dropdown;

  signals:
    void displayModeUpdated(const DisplayMode& display_mode);
};

#endif // SETTINGSWINDOW_H
