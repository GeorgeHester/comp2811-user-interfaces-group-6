#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QResizeEvent>
#include <QPaintEvent>

#include "header.h"
#include "displaymode.h"
#include "window.h"

class BaseWindow : public QWidget
{
    Q_OBJECT

  public:
    // BaseWindow(QWidget* parent = nullptr);

  signals:
    virtual void currentWindowUpdated(Window to, Window from);

  protected:
    virtual void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event)
    {
        QStyleOption style_option;
        style_option.init(this);
        QPainter painter(this);
        style()->drawPrimitive(
          QStyle::PE_Widget, &style_option, &painter, this);
    };
};

#endif // BASEWINDOW_H
