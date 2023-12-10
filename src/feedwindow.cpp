#include "feedwindow.h"

FeedWindow::FeedWindow(QWidget* parent)
  : QWidget(parent){

  };

void
FeedWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};