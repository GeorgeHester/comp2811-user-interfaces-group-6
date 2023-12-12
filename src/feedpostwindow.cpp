#include "feedpostwindow.h"

FeedPostWindow::FeedPostWindow(QWidget* parent)
  : QWidget(parent)
{
    // Create base layout of window
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);

    // Add header to window
    this->header = new Header("Settings", this);
    layout->addWidget(this->header);

    // Create scroll area to store the posts
    this->scroll_area = new QScrollArea(this);
    this->scroll_area->setObjectName("FeedWindowScrollArea");
    this->scroll_area->setAlignment(Qt::AlignTop);
    this->scroll_area->setHorizontalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->scroll_area->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    this->scroll_area->setWidgetResizable(true);
    layout->addWidget(this->scroll_area);

    // Create a scroll area widget to hold the area contents
    this->scroll_area_widget = new QWidget(this->scroll_area);
    this->scroll_area->setWidget(this->scroll_area_widget);

    // Create the layout for the scroll area widget
    this->scroll_area_layout = new QBoxLayout(
      QBoxLayout::Direction::TopToBottom, this->scroll_area_widget);
    this->scroll_area_layout->setAlignment(Qt::AlignTop);
    this->scroll_area_layout->setMargin(0);
    this->scroll_area_layout->setSpacing(0);

    // Draw in posts
    this->paintPosts();

    // Connect handler for header navigation clicked
    connect(this->header,
            &Header::rightButtonClicked,
            [this]()
            {
                emit currentWindowUpdated(Window::Settings, Window::FeedPost);
            });
};

void
FeedPostWindow::paintPosts()
{
    this->posts.clear();

    for (Post post : Store::posts)
    {
        QWidget* post_header = new QWidget(this->scroll_area_widget);
        post_header->setObjectName("FeedWindowScrollAreaPostHeader");
        this->scroll_area_layout->addWidget(post_header);

        QBoxLayout* post_header_layout =
          new QBoxLayout(QBoxLayout::Direction::LeftToRight, post_header);
        post_header_layout->setSpacing(0);

        QLabel* post_header_username_label = new QLabel(post_header);
        post_header_username_label->setObjectName(
          "FeedWindowScrollAreaPostHeaderLabel");
        post_header_username_label->setAlignment(Qt::AlignLeft);
        post_header_username_label->setText(post.username);
        post_header_layout->addWidget(post_header_username_label);

        QLabel* post_header_time_label = new QLabel(post_header);
        post_header_time_label->setObjectName(
          "FeedWindowScrollAreaPostHeaderLabel");
        post_header_time_label->setAlignment(Qt::AlignRight);
        post_header_time_label->setText(post.post_time);
        post_header_layout->addWidget(post_header_time_label);

        QFrame* post_frame = new QFrame(this->scroll_area_widget);
        post_frame->setObjectName("FeedWindowScrollAreaFrame");
        post_frame->setFixedSize(INT_MAX, INT_MAX);
        this->scroll_area_layout->addWidget(post_frame);

        QLabel* post_caption_label = new QLabel(this->scroll_area_widget);
        post_caption_label->setObjectName(
          "FeedWindowScrollAreaPostCaptionLabel");
        post_caption_label->setAlignment(Qt::AlignLeft);
        post_caption_label->setText(post.post_caption);
        this->scroll_area_layout->addWidget(post_caption_label);

        QBoxLayout* post_frame_layout =
          new QBoxLayout(QBoxLayout::Direction::TopToBottom, post_frame);
        post_frame_layout->setAlignment(Qt::AlignTop);
        post_frame_layout->setMargin(0);
        post_frame_layout->setSpacing(0);

        QVideoWidget* post_video_widget = new QVideoWidget(post_frame);
        post_video_widget->setAspectRatioMode(
          Qt::AspectRatioMode::KeepAspectRatioByExpanding);
        post_frame_layout->addWidget(post_video_widget);

        QMediaPlaylist* post_playlist = new QMediaPlaylist(post_frame);
        post_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        post_playlist->addMedia(QUrl("qrc:/" + post.post_url));
        post_playlist->setCurrentIndex(0);

        QMediaPlayer* post_player = new QMediaPlayer(post_frame);
        post_player->setMuted(true);
        post_player->setVideoOutput(post_video_widget);
        post_player->setPlaylist(post_playlist);
        post_player->play();

        PostUi post_ui;
        post_ui.frame = post_frame;
        post_ui.video_widget = post_video_widget;

        this->posts.append(post_ui);
    };
};

void
FeedPostWindow::resizeScrollArea(int window_width, int window_height)
{
    // Get new sizes
    int header_height = this->header->height();

    // Update the geometry for the scroll area
    this->scroll_area->setGeometry(
      0, header_height, window_width, window_height - header_height);
};

void
FeedPostWindow::resizePosts(int parent_width, int parent_height)
{
    for (int index = 0; index < this->posts.length(); index++)
    {
        QFrame* frame = this->posts[index].frame;

        // Update the size for the frame
        frame->setFixedSize(parent_width - 14, (parent_width - 14) * 5 / 4);

        // Update the size for the frame content
        this->resizeFrameVideoWidget(frame->width(),
                                     frame->height(),
                                     frame,
                                     this->posts[index].video_widget);
    };
};

void
FeedPostWindow::resizeFrameVideoWidget(int parent_width,
                                       int parent_height,
                                       QFrame* frame,
                                       QVideoWidget* video_widget)
{
    // Set default values
    int frame_radius = 16;

    // Update the size for the frame
    video_widget->setFixedSize(parent_width - 24 - 4, parent_height - 4);

    // Set rounded mask
    QPainterPath* painter_path = new QPainterPath();
    painter_path->addRoundedRect(
      QRectF(0, 0, parent_width - 24 - 4, parent_height - 4),
      frame_radius,
      frame_radius);
    video_widget->setMask(painter_path->toFillPolygon().toPolygon());
};

void
FeedPostWindow::resizeEvent(QResizeEvent* event)
{
    // Handle resizing the scroll area
    this->resizeScrollArea(event->size().width(), event->size().height());

    // Handle resizing the posts
    this->resizePosts(this->scroll_area->width(), this->scroll_area->height());

    QWidget::resizeEvent(event);
};

void
FeedPostWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};