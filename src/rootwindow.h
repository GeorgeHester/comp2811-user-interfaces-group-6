#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QMainWindow>
#include <QStyleOption>
#include <QPainter>
#include <QtGlobal>

#include "resource.h"
#include "window.h"
#include "capturewindow.h"
#include "settingswindow.h"
#include "postwindow.h"
#include "feedprewindow.h"
#include "feedpostwindow.h"
#include "displaymode.h"
#include "footer.h"

class RootWindow : public QMainWindow
{
    Q_OBJECT

  public:
    RootWindow(QWidget* parent = nullptr);
    QLabel* label;

  private:
    Window previous_window;
    QStackedWidget* stacked_widget;
    CaptureWindow* capture_window;
    SettingsWindow* settings_window;
    FeedPreWindow* feed_pre_window;
    FeedPostWindow* feed_post_window;
    PostWindow* post_window;
    QString qss_light_mode;
    QString qss_dark_mode;
    QString qss_light_high_contrast_mode;
    QString qss_dark_high_contrast_mode;

  protected:
    void refreshWindow(Window window);
    void updateCurrentWindow(Window to, Window from);
    void updateDisplayMode(DisplayMode display_mode);
    void updateFontSizeScale(double scale);
};

#endif // ROOTWINDOW_H