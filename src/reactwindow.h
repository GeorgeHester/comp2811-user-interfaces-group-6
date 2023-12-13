#ifndef REACTWINDOW_H
#define REACTWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QBoxLayout>
#include <QPushButton>
#include <QVideoWidget>
#include <QFrame>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPainterPath>
#include <QLineEdit>

#include "header.h"
#include "window.h"
#include "store.h"

class ReactWindow : public QWidget
{
    Q_OBJECT

  public:
    ReactWindow(QWidget* parent = nullptr);

    void refresh();

  signals:
    void currentWindowUpdated(Window to, Window from);

  private:
    QWidget* frame_container;
    QFrame* frame;
    QVideoWidget* video_widget;
    QMediaPlaylist* playlist;
    QMediaPlayer* player;

  protected:
    void resizeFrameContainer(int parent_width, int parent_height);
    void resizeFrame(int parent_width, int parent_height);
    void resizeVideoWidget(int parent_width, int parent_height);

    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // REACTWINDOW_H
