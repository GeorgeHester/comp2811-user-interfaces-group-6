#include "capturewindow.h"

CaptureWindow::CaptureWindow(QWidget* parent)
  : QWidget(parent)
{
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    this->header = new Header(this);
    layout->addWidget(this->header);

    this->viewfinder_frame = new QFrame(this);
    this->viewfinder_frame->setObjectName("CaptureWindowViewfinderFrame");
    layout->addWidget(viewfinder_frame);

    QBoxLayout* viewfinder_frame_layout = new QBoxLayout(
      QBoxLayout::Direction::TopToBottom, this->viewfinder_frame);
    viewfinder_frame_layout->setAlignment(Qt::AlignTop);
    viewfinder_frame_layout->setMargin(0);
    viewfinder_frame_layout->setSpacing(0);
    this->viewfinder_frame->setLayout(viewfinder_frame_layout);

    this->viewfinder = new QCameraViewfinder(this);
    this->viewfinder->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    viewfinder_frame_layout->addWidget(this->viewfinder);

    QCamera* camera = new QCamera(QCamera::FrontFace, this);
    camera->setViewfinder(this->viewfinder);

    camera->start();
    this->paintCameraViewfinder(this->width(), this->height());
};

void
CaptureWindow::paintCameraViewfinder(int width, int height)
{
    // Get the new sizes
    int frame_margin = 12;
    int frame_border = 2;
    int frame_radius = 16;
    int header_height = this->header->height();

    // Update the geometry for the viewfinder frame view which contains the
    // viewfinder
    this->viewfinder_frame->setGeometry(
      frame_margin,
      this->header->height() + frame_margin,
      width - 24,
      std::min((width - 24) * 5 / 4, height - header_height - 24));

    this->viewfinder->setGeometry(
      frame_border,
      frame_border,
      width - 24 - (frame_border * 2),
      std::min((width - 24 - (frame_border * 2)) * 5 / 4,
               height - header_height - 24 - (frame_border * 2)));

    QPainterPath* viewfinder_painter_path = new QPainterPath();
    viewfinder_painter_path->addRoundedRect(
      this->viewfinder->rect(), frame_radius, frame_radius);
    this->viewfinder->setMask(
      viewfinder_painter_path->toFillPolygon().toPolygon());
};

void
CaptureWindow::resizeEvent(QResizeEvent* event)
{
    this->paintCameraViewfinder(event->size().width(), event->size().height());
    QWidget::resizeEvent(event);
};

void
CaptureWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    // painter.setRenderHint(QPainter::RenderHint::HighQualityAntialiasing);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};