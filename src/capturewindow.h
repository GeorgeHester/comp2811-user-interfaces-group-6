#ifndef CAPTUREWINDOW_H
#define CAPTUREWINDOW_H

#include <QWidget>
#include <QBoxLayout>
#include <QCamera>
#include <QCameraInfo>
#include <QVideoWidget>
#include <QLayout>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsRectItem>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsColorizeEffect>
#include <QCameraViewfinder>
#include <QStyleOption>
#include <QPainter>
#include <QResizeEvent>
#include <QSize>
#include <QFrame>
#include <QPainterPath>

#include "header.h"

class CaptureWindow : public QWidget
{
    Q_OBJECT

  public:
    CaptureWindow(QWidget* parent = nullptr);

  protected:
    QFrame* viewfinder_frame;
    QCameraViewfinder* viewfinder;
    Header* header;

    void paintCameraViewfinder(int width, int height);
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // CAPTUREWINDOW_H
