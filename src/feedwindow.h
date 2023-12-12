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
#include <QMediaPlaylist>
#include <QRectF>
#include <QString>

#include "window.h"
#include "header.h"
#include "post.h"
#include "store.h"

class FeedWindow : public QWidget
{
    Q_OBJECT

  public:
    FeedWindow(QWidget* parent = nullptr);

  private:
    Header* header;
    QScrollArea* scroll_area;
    QWidget* scroll_area_widget;
    QBoxLayout* scroll_area_layout;
    QVector<PostUi> posts;
    QVector<PostBlank> blanks;
    QVector<QFrame*> frames;
    QVector<QVideoWidget*> frame_video_widgets;

  signals:
    void currentWindowUpdated(Window to, Window from);

  protected:
    void paintPosts();
    void resizeScrollArea(int window_width, int window_height);
    void resizePosts(int parent_width, int parent_height);
    void resizePostBlanks(int parent_width, int parent_height);
    void resizeFrameVideoWidget(int parent_width,
                                int parent_height,
                                QFrame* frame,
                                QVideoWidget* video_widget);
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // FEEDWINDOW_H
