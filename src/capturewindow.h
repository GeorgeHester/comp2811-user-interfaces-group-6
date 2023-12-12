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
#include <QShowEvent>
#include <QTimer>
#include <QMediaRecorder>
#include <QTemporaryFile>
#include <QVideoEncoderSettings>

#include "header.h"
#include "window.h"
#include "store.h"

class CaptureWindow : public QWidget
{
    Q_OBJECT

  public:
    CaptureWindow(QWidget* parent = nullptr);

  signals:
    void currentWindowUpdated(Window to, Window from);

  protected:
    QFrame* viewfinder_frame;
    QCameraViewfinder* viewfinder;
    QCamera* camera;
    Header* header;
    QPushButton* capture_button;
    QLabel* countdown_label;
    QTimer* countdown_timer;

    int countdown_remaining_time;

    QTemporaryFile* output_file;
    QMediaRecorder* recorder;

    void setRecorderSettings();

    void captureButtonClicked();
    void updateCaptureCountdown();

    void resizeViewfinderFrame(int parent_width, int parent_height);
    void resizeViewfinder(int parent_width, int parent_height);
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // CAPTUREWINDOW_H
