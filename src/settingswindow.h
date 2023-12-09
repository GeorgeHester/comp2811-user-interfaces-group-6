#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QComboBox>
#include <QString>
#include <QRect>
#include <QStyleOption>
#include <QPainter>

#include "header.h"
#include "settingshandler.h"
#include "displaymode.h"
#include "rootwindow.h"

class SettingsWindow : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWidget)

  public:
    SettingsWindow(QWidget* parent = nullptr);

    QComboBox* display_mode_dropdown;

  signals:
    void displayModeUpdated(const DisplayMode& display_mode);

  private:
    void updateDisplayModeDropdownWidth();

  protected:
    void paintEvent(QPaintEvent* event);
};

#endif // SETTINGSWINDOW_H
