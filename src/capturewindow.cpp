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

    // Add header to window
    this->header = new Header("Back", this);
    layout->addWidget(this->header);

    // Create the frame to store the camera
    this->viewfinder_frame = new QFrame(this);
    this->viewfinder_frame->setObjectName("CaptureWindowViewfinderFrame");
    layout->addWidget(this->viewfinder_frame);

    // Create label to hold countdown value
    this->countdown_label = new QLabel(this);
    this->countdown_label->setObjectName("CaptureWindowCountdownLabel");
    this->countdown_label->setText("Ready");
    layout->addWidget(this->countdown_label);

    // Create push button to allow capture
    this->capture_button = new QPushButton("Capture", this);
    layout->addWidget(this->capture_button);

    //
    //
    //
    //

    // Create timer and set the interval for updating the ui
    this->countdown_timer = new QTimer(this);
    this->countdown_timer->setInterval(1000);

    //
    //
    //
    //

    // Create the layout for the viewfinder frame to hold the viewfinder
    QBoxLayout* viewfinder_frame_layout = new QBoxLayout(
      QBoxLayout::Direction::TopToBottom, this->viewfinder_frame);
    viewfinder_frame_layout->setAlignment(Qt::AlignTop);
    viewfinder_frame_layout->setMargin(0);
    viewfinder_frame_layout->setSpacing(0);

    //
    //
    //
    //

    // Create the camera viewfinder and set its default
    this->viewfinder = new QCameraViewfinder(this);
    this->viewfinder->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    viewfinder_frame_layout->addWidget(this->viewfinder);

    // Create the camera object
    this->camera = new QCamera(QCameraInfo::defaultCamera(), this->viewfinder);
    this->camera->setViewfinder(this->viewfinder);

    // Update the capture mode
    // if (this->camera->isCaptureModeSupported(
    //      QCamera::CaptureMode::CaptureVideo))
    //   this->camera->setCaptureMode(QCamera::CaptureMode::CaptureVideo);

    // Start the camera
    this->camera->start();

    //
    //
    //
    //

    // Create temporary file to store the users video
    // this->output_file = new QTemporaryFile(this);

    // Create recorder
    this->recorder = new QMediaRecorder(this->camera);
    // this->camera->setCaptureMode(QCamera::CaptureMode::CaptureVideo);

    // connect(this->recorder,
    //         QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
    //         [=](QMediaRecorder::Error error)
    //         {
    //             qDebug() << this->recorder->errorString();
    //             qDebug() << error;
    //         });

    connect(this->recorder,
            QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            [=](QMediaRecorder::Error error)
            {
                qDebug() << this->recorder->errorString();
                qDebug() << error;
            });

    connect(this->recorder,
            &QMediaRecorder::stateChanged,
            [](QMediaRecorder::State state)
            {
                qDebug() << "stateChanged: " << state;
            });

    connect(this->recorder,
            &QMediaRecorder::statusChanged,
            [](QMediaRecorder::Status status)
            {
                qDebug() << "statusChanged: " << status;
            });

    connect(this->recorder,
            &QMediaRecorder::actualLocationChanged,
            [](const QUrl& location)
            {
                qDebug() << "actualLocationChanged: " << location.toString();
            });

    // Connect handler for header navigation clicked
    connect(this->header,
            &Header::rightButtonClicked,
            [this]()
            {
                emit currentWindowUpdated(Window::Feed, Window::Capture);
            });

    // Connect handler for capture button clicked
    connect(this->capture_button,
            &QPushButton::clicked,
            [this]()
            {
                this->captureButtonClicked();
            });

    // Connect handler for each iteration of the timer
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
    QVideoEncoderSettings recorder_settings = this->recorder->videoSettings();
    recorder_settings.setCodec("");
    recorder_settings.setQuality(QMultimedia::EncodingQuality::NormalQuality);
    recorder_settings.setResolution(QSize(-1, -1));
    recorder_settings.setFrameRate(0);
    this->recorder->setEncodingSettings(
      this->recorder->audioSettings(), recorder_settings, "mp4");

    this->camera->unload();
    this->camera->start();
};

void
CaptureWindow::captureButtonClicked()
{
    // this->output_file->open();
    // Store::output_file_name = this->output_file->fileName();
    // this->recorder->setOutputLocation(
    // QUrl::fromLocalFile(Store::output_file_name));

    this->capture_button->setDisabled(true);

    this->countdown_remaining_time = 5000;
    this->countdown_timer->start();

    this->setRecorderSettings();
    this->recorder->setOutputLocation(QUrl::fromLocalFile("test.mp4"));

    qDebug() << this->recorder->actualLocation();

    this->recorder->record();

    qDebug() << this->recorder->actualLocation();
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
};

void
CaptureWindow::resizeViewfinder(int parent_width, int parent_height)
{
    // Get the new sizes
    int header_height = this->header->height();
    int frame_radius = 16;
    int new_width = parent_width - 24 - 4;
    int new_height = parent_height - 12 - 4;

    // Set viewfinder size
    this->viewfinder->setGeometry(14, 2, new_width, new_height);

    // Set rounded mask
    QPainterPath* painter_path = new QPainterPath();
    painter_path->addRoundedRect(
      QRectF(0, 0, new_width, new_height), frame_radius, frame_radius);
    this->viewfinder->setMask(painter_path->toFillPolygon().toPolygon());
};

void
CaptureWindow::resizeViewfinderFrame(int parent_width, int parent_height)
{
    // Get the new sizes
    int header_height = this->header->height();
    int new_width = parent_width;
    int new_height =
      new_width * 5 /
      4; // std::min(new_width * 5 / 4, new_width - header_height);

    // Update the size for the viewfinder frame
    this->viewfinder_frame->setGeometry(
      0, header_height, new_width, new_height);

    // Update the viewfinder
    this->resizeViewfinder(this->viewfinder_frame->width(),
                           this->viewfinder_frame->height());
};

void
CaptureWindow::resizeEvent(QResizeEvent* event)
{
    // Handle resizing the viewfinder
    this->resizeViewfinderFrame(event->size().width(), event->size().height());

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

// void
// CaptureWindow::showEvent(QShowEvent* event)
//{
//     QWidget::showEvent(event);
// };
