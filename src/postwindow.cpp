#include "postwindow.h"

PostWindow::PostWindow(QWidget* parent)
  : QWidget(parent)
{
    // Create the layout for the widget
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);

    // Create a header with a back button
    this->header = new Header(this);
    layout->addWidget(this->header);

    // Create a container for the frame
    this->frame_container = new QWidget(this);

    // Create the layout for the frame containrer
    QBoxLayout* frame_container_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this->frame_container);
    frame_container_layout->setAlignment(Qt::AlignTop);
    frame_container_layout->setMargin(0);
    frame_container_layout->setSpacing(0);

    // Create the frame to store the camera
    this->frame = new QFrame(this->frame_container);
    this->frame->setObjectName("PostWindowFrame");
    this->frame->setFixedSize(0, 0);
    frame_container_layout->addWidget(this->frame);

    QBoxLayout* frame_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this->frame);
    frame_layout->setAlignment(Qt::AlignTop);
    frame_layout->setMargin(0);
    frame_layout->setSpacing(0);

    this->video_widget = new QVideoWidget(this->frame);
    this->video_widget->setAspectRatioMode(
      Qt::AspectRatioMode::KeepAspectRatioByExpanding);
    frame_layout->addWidget(video_widget);

    this->playlist = new QMediaPlaylist(this->frame);
    this->playlist->setPlaybackMode(QMediaPlaylist::Loop);
    qDebug() << Store::post_file_name;

    this->player = new QMediaPlayer(this->frame);
    this->player->setMuted(true);
    this->player->setVideoOutput(this->video_widget);
    this->player->setPlaylist(playlist);

    // Create a post button
    this->post_button = new QPushButton("Post", this);
    this->post_button->setObjectName("PostWindowPostButton");
    layout->addWidget(this);

    // Connect handler for post button clicked
    connect(this->post_button,
            &QPushButton::clicked,
            [this]()
            {
                emit currentWindowUpdated(Window::Feed, Window::Capture);
            });
};

void
PostWindow::refresh()
{
    qDebug() << Store::post_file_name;
    this->playlist->clear();
    this->playlist->addMedia(QUrl(Store::post_file_name));
    this->playlist->setCurrentIndex(0);
    this->player->play();
};

void
PostWindow::resizeVideoWidget(int parent_width, int parent_height)
{
    // Set default values
    int frame_radius = 16;

    // Update the size of the video widget
    this->video_widget->setFixedSize(parent_width - 24 - 4, parent_height - 4);

    // Set rounded mask on the video widget
    QPainterPath* painter_path = new QPainterPath();
    painter_path->addRoundedRect(
      QRectF(0, 0, parent_width - 24 - 4, parent_height - 4),
      frame_radius,
      frame_radius);
    this->video_widget->setMask(painter_path->toFillPolygon().toPolygon());
};

void
PostWindow::resizeFrame(int parent_width, int parent_height)
{
    // Update the size of the frame
    this->frame->setFixedSize(parent_width, parent_width * 5 / 4);

    // Update the size of the video widget
    this->resizeVideoWidget(this->frame->width(), this->frame->height());
};

void
PostWindow::resizeFrameContainer(int parent_width, int parent_height)
{
    // Get new sizes
    int header_height = this->header->height();

    // Update the container geometry
    this->frame_container->setGeometry(
      0, header_height, parent_width, parent_height);

    // Update post button geomerty
    this->post_button->setGeometry(
      0, header_height + parent_width * 5 / 4, parent_width, 40 + 24);
};

void
PostWindow::resizeEvent(QResizeEvent* event)
{
    // Resize the frame container
    this->resizeFrameContainer(event->size().width(), event->size().height());

    // Resize the frame
    this->resizeFrame(this->frame_container->width(),
                      this->frame_container->height());

    QWidget::resizeEvent(event);
};

void
PostWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};
