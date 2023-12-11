#ifndef FEEDWINDOW_H
#define FEEDWINDOW_H

#include <QWidget>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QVideoWidget>
#include <QUrl>
#include <QBoxLayout>
#include <QDebug>
#include <QScrollArea>
#include <QVector>
#include <QResizeEvent>

#include "window.h"
#include "header.h"

class FeedWindow : public QWidget
{
    Q_OBJECT

  public:
    FeedWindow(QWidget* parent = nullptr);

  private:
    Header* header;
    QScrollArea* scroll_area;
    QVector<QFrame*> frames;
    void addPost();

  signals:
    void currentWindowUpdated(Window to, Window from);

  protected:
    void resizeScrollArea(int window_width, int window_height);
    void resizeFrames(int scroll_area_width, int scroll_area_height);
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // FEEDWINDOW_H
