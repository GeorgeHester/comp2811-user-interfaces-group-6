#ifndef FEEDWINDOW_H
#define FEEDWINDOW_H

#include <QWidget>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

class FeedWindow : public QWidget
{
    Q_OBJECT

  public:
    FeedWindow(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // FEEDWINDOW_H
