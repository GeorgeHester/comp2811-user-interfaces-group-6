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

    // Create a header
    this->header = new Header(this);
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
    this->frame->setObjectName("PostWindowFrame");
    this->frame->setFixedSize(0, 0);
    frame_container_layout->addWidget(this->frame);

    // Create the layout for the frame
    QBoxLayout* frame_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this->frame);
    frame_layout->setAlignment(Qt::AlignTop);
    frame_layout->setMargin(0);
    frame_layout->setSpacing(0);

    // Create a video widget
    this->video_widget = new QVideoWidget(this->frame);
    this->video_widget->setAspectRatioMode(
      Qt::AspectRatioMode::KeepAspectRatioByExpanding);

    // Create a playlist
    this->playlist = new QMediaPlaylist(this->frame);
    this->playlist->setPlaybackMode(QMediaPlaylist::Loop);

    // Create a player
    this->player = new QMediaPlayer(this->frame);
    this->player->setMuted(true);
    this->player->setVideoOutput(this->video_widget);
    this->player->setPlaylist(playlist);

    // Create a caption input
    QLineEdit* caption_input = new QLineEdit(this);
    caption_input->setObjectName("PostWindowCaptionInput");
    caption_input->setPlaceholderText("Caption");
    layout->addWidget(caption_input);

    // Create a post button
    this->post_button = new QPushButton("Post", this);
    this->post_button->setObjectName("PostWindowPostButton");
    layout->addWidget(this->post_button);

    // Connect handler for post button clicked
    connect(this->post_button,
            &QPushButton::clicked,
            [this]()
            {
                emit currentWindowUpdated(Window::FeedPost, Window::Capture);
            });
};

void
PostWindow::refresh()
{
    qDebug() << "Loading: " << Store::temporary_file_name;

    // Clear out the current playlist
    this->playlist->clear();

    // Add the temporary file as the media file
    this->playlist->addMedia(QUrl::fromLocalFile(Store::temporary_file_name));

    // Update the playlist and set the player to start
    this->playlist->setCurrentIndex(0);
    this->player->play();
};

void
PostWindow::resizeVideoWidget(int parent_width, int parent_height)
{
    // Set default values
    int frame_radius = 16;

    // Update the video widget size
    this->video_widget->setGeometry(2, 2, parent_width - 4, parent_height - 4);

    // Set rounded mask on the video widget
    QPainterPath* painter_path = new QPainterPath();
    painter_path->addRoundedRect(
      QRect(0, 0, parent_width - 4, parent_height - 4),
      frame_radius,
      frame_radius);
    this->video_widget->setMask(painter_path->toFillPolygon().toPolygon());
};

void
PostWindow::resizeFrame(int parent_width, int parent_height)
{
    // Update the frame size
    this->frame->setFixedSize(parent_width, parent_height);

    // Update the video widget size and mask
    this->resizeVideoWidget(this->frame->width(), this->frame->height());
};

void
PostWindow::resizeFrameContainer(int parent_width, int parent_height)
{
    // Update the frame container size
    this->frame_container->setFixedSize(parent_width - 24,
                                        (parent_width - 24) * 5 / 4);
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
