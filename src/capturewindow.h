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

#include "header.h"

class CaptureWindow : public QWidget
{
    Q_OBJECT

  public:
    CaptureWindow();

  protected:
    void paintEvent(QPaintEvent*);
};

#endif // CAPTUREWINDOW_H
