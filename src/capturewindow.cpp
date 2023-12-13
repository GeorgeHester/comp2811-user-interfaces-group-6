#include "capturewindow.h"

CaptureWindow::CaptureWindow(QWidget* parent)
  : QWidget(parent)
{
    // Create the layout for the widget
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);

    // Create a header
    this->header = new Header("Back", this);
    layout->addWidget(this->header);

    // Create a frame container
    this->frame_container = new QWidget(this);
    layout->addWidget(this->frame_container, 0, Qt::AlignCenter);

    // Create the layout for the frame containrer
    QBoxLayout* frame_container_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this->frame_container);
    frame_container_layout->setAlignment(Qt::AlignCenter);
    frame_container_layout->setMargin(0);
    frame_container_layout->setSpacing(0);

    // Create a frame
    this->frame = new QFrame(this->frame_container);
    this->frame->setObjectName("CaptureWindowFrame");
    this->frame->setFixedSize(0, 0);
    frame_container_layout->addWidget(this->frame);

    // Create the layout for the frame
    QBoxLayout* frame_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this->frame);
    frame_layout->setAlignment(Qt::AlignTop);
    frame_layout->setMargin(0);
    frame_layout->setSpacing(0);

    // Create a camera viewfinder
    this->viewfinder = new QCameraViewfinder(this->frame);
    this->viewfinder->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    // frame_layout->addWidget(this->viewfinder);

    // Create a camera
    this->camera = new QCamera(QCameraInfo::defaultCamera(), this->viewfinder);

    // Create a recorder
    this->recorder = new QMediaRecorder(this->camera);
    this->recorder->setMuted(true);

    // Update the camera viewfinder
    this->camera->setViewfinder(this->viewfinder);

    // Update the camera capture mode
    if (this->camera->isCaptureModeSupported(
          QCamera::CaptureMode::CaptureVideo))
        this->camera->setCaptureMode(QCamera::CaptureMode::CaptureVideo);

    // Start the camera
    this->camera->start();

    // Create a label
    this->countdown_label = new QLabel(this);
    this->countdown_label->setObjectName("CaptureWindowCountdownLabel");
    this->countdown_label->setAlignment(Qt::AlignCenter);
    this->countdown_label->setText("Ready");
    layout->addWidget(this->countdown_label);

    // Create a capture button
    this->capture_button = new QPushButton("Capture", this);
    this->capture_button->setObjectName("CaptureWindowCaptureButton");
    layout->addWidget(this->capture_button);

    // Create a timer
    this->countdown_timer = new QTimer(this);
    this->countdown_timer->setInterval(1000);

    // Connect handler for header navigation clicked
    connect(this->header,
            &Header::rightButtonClicked,
            [this]()
            {
                emit currentWindowUpdated(Window::FeedPre, Window::Capture);
            });

    // Connect handler for capture button clicked
    connect(this->capture_button,
            &QPushButton::clicked,
            [this]()
            {
                this->captureButtonClicked();
            });

    // Connect handler for timer iteration
    connect(this->countdown_timer,
            &QTimer::timeout,
            [this]()
            {
                this->updateCaptureCountdown();
            });
};

void
CaptureWindow::setRecorderSettings()
{
    // Update the recorder settings
    QVideoEncoderSettings recorder_settings = this->recorder->videoSettings();
    recorder_settings.setCodec("");
    recorder_settings.setQuality(QMultimedia::EncodingQuality::NormalQuality);
    recorder_settings.setResolution(QSize(-1, -1));
    recorder_settings.setFrameRate(0);
    this->recorder->setEncodingSettings(
      this->recorder->audioSettings(), recorder_settings, "mp4");

    // Unload the camera then restart
    this->camera->unload();
    this->camera->start();
};

void
CaptureWindow::captureButtonClicked()
{
    QTemporaryFile* temporary_file = new QTemporaryFile(this);
    temporary_file->setAutoRemove(true);
    temporary_file->open();

    Store::temporary_file_name = temporary_file->fileName() + ".mp4";

    this->capture_button->setDisabled(true);

    this->countdown_remaining_time = 5000;
    this->countdown_timer->start();

    qDebug() << Store::temporary_file_name;

    this->setRecorderSettings();
    this->recorder->setOutputLocation(
      QUrl::fromLocalFile(Store::temporary_file_name));

    this->recorder->record();
};

void
CaptureWindow::updateCaptureCountdown()
{
    if (this->countdown_remaining_time > 0)
    {
        this->countdown_remaining_time -= 1000;
        this->countdown_label->setText(
          QString::number(this->countdown_remaining_time / 1000));
        return;
    };

    this->countdown_timer->stop();
    this->recorder->stop();

    emit currentWindowUpdated(Window::PostScreen, Window::Capture);
};

void
CaptureWindow::resizeViewfinder(int parent_width, int parent_height)
{
    // Set default values
    int frame_radius = 16;

    // Update the viewfinder size
    this->viewfinder->setGeometry(2, 2, parent_width - 4, parent_height - 4);

    // Set rounded mask on the video widget
    QPainterPath* painter_path = new QPainterPath();
    painter_path->addRoundedRect(
      QRectF(0, 0, parent_width - 4, parent_height - 4),
      frame_radius,
      frame_radius);
    this->viewfinder->setMask(painter_path->toFillPolygon().toPolygon());
};

void
CaptureWindow::resizeFrame(int parent_width, int parent_height)
{
    // Update the frame size
    this->frame->setFixedSize(parent_width, parent_height);

    // Update the viewfinder size and mask
    this->resizeViewfinder(this->frame->width(), this->frame->height());
};

void
CaptureWindow::resizeFrameContainer(int parent_width, int parent_height)
{
    // Update the frame container size
    this->frame_container->setFixedSize(parent_width - 24,
                                        (parent_width - 24) * 5 / 4);
};

void
CaptureWindow::resizeEvent(QResizeEvent* event)
{
    // Resize the frame container
    this->resizeFrameContainer(event->size().width(), event->size().height());

    // Resize the frame
    this->resizeFrame(this->frame_container->width(),
                      this->frame_container->height());

    QWidget::resizeEvent(event);
};

void
CaptureWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};