#ifndef FRAME_H
#define FRAME_H

#include <QFrame>
#include <QMouseEvent>

class QFrameClickable : public QFrame
{
    Q_OBJECT

  public:
    QFrameClickable(QWidget* parent = nullptr)
      : QFrame(parent){};

  signals:
    void clicked();

  protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton) emit clicked();

        QFrame::mousePressEvent(event);
    };
};

#endif // FRAME_H
