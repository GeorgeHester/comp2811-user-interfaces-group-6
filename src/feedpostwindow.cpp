#include "feedpostwindow.h"

FeedPostWindow::FeedPostWindow(QWidget* parent)
  : QWidget(parent)
{
    // Create the layout for the widget
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);

    // Create a header
    this->header = new Header("Settings", this);
    layout->addWidget(this->header);

    // Create a scroll area
    this->scroll_area = new QScrollArea(this);
    this->scroll_area->setObjectName("FeedWindowScrollArea");
    this->scroll_area->setAlignment(Qt::AlignTop);
    this->scroll_area->setHorizontalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->scroll_area->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->scroll_area->setWidgetResizable(true);
    layout->addWidget(this->scroll_area);

    // Create a scroll area container
    this->scroll_area_widget = new QWidget(this->scroll_area);
    this->scroll_area->setWidget(this->scroll_area_widget);

    // Create the layout for the scroll area container
    this->scroll_area_layout = new QBoxLayout(
      QBoxLayout::Direction::TopToBottom, this->scroll_area_widget);
    this->scroll_area_layout->setAlignment(Qt::AlignTop);
    this->scroll_area_layout->setMargin(0);
    this->scroll_area_layout->setSpacing(0);

    // Paint posts
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
    // Clear the current posts
    this->posts.clear();

    // Loop through imported posts
    for (Post post : Store::posts)
    {
        // Crate a post header
        QWidget* post_header = new QWidget(this->scroll_area_widget);
        post_header->setObjectName("FeedWindowScrollAreaHeader");
        this->scroll_area_layout->addWidget(post_header);

        // Create the layout for the post header
        QBoxLayout* post_header_layout =
          new QBoxLayout(QBoxLayout::Direction::LeftToRight, post_header);
        post_header_layout->setAlignment(Qt::AlignTop);
        post_header_layout->setSpacing(0);

        // Create a post header username label
        QLabel* post_header_username_label = new QLabel(post_header);
        post_header_username_label->setAlignment(Qt::AlignLeft);
        post_header_username_label->setText(post.username);
        post_header_layout->addWidget(post_header_username_label);

        // Create a post header time label
        QLabel* post_header_time_label = new QLabel(post_header);
        post_header_time_label->setAlignment(Qt::AlignRight);
        post_header_time_label->setText(post.post_time);
        post_header_layout->addWidget(post_header_time_label);

        // Create a post frame
        QFrameClickable* post_frame =
          new QFrameClickable(this->scroll_area_widget);
        post_frame->setObjectName("FeedWindowScrollAreaFrame");
        post_frame->setFixedSize(0, 0);
        this->scroll_area_layout->addWidget(post_frame);

        // Create a post caption label
        QLabel* post_caption_label = new QLabel(this->scroll_area_widget);
        post_caption_label->setObjectName("FeedWindowScrollAreaCaptionLabel");
        post_caption_label->setAlignment(Qt::AlignLeft);
        post_caption_label->setText(post.post_caption);
        this->scroll_area_layout->addWidget(post_caption_label);

        // Create the layout for the post blank frame
        QBoxLayout* post_frame_layout =
          new QBoxLayout(QBoxLayout::Direction::TopToBottom, post_frame);
        post_frame_layout->setAlignment(Qt::AlignCenter);
        post_frame_layout->setMargin(0);
        post_frame_layout->setSpacing(0);

        // Create a video widget
        QVideoWidget* post_video_widget = new QVideoWidget(post_frame);
        post_video_widget->setAspectRatioMode(
          Qt::AspectRatioMode::KeepAspectRatioByExpanding);
        // post_frame_layout->addWidget(post_video_widget);

        // Create a playlist
        QMediaPlaylist* post_playlist = new QMediaPlaylist(post_frame);
        post_playlist->setPlaybackMode(QMediaPlaylist::Loop);
        post_playlist->addMedia(QUrl("qrc:/" + post.post_url));
        post_playlist->setCurrentIndex(0);

        // Create a player
        QMediaPlayer* post_player = new QMediaPlayer(post_frame);
        post_player->setMuted(true);
        post_player->setVideoOutput(post_video_widget);
        post_player->setPlaylist(post_playlist);
        post_player->play();

        // Connect handler for post button clicked
        connect(post_frame,
                &QFrameClickable::clicked,
                [this, post]()
                {
                    Store::selected_post_url = post.post_url;
                    emit currentWindowUpdated(Window::React, Window::FeedPost);
                });

        // Create a post
        PostUi post_ui;
        post_ui.frame = post_frame;
        post_ui.video_widget = post_video_widget;

        // Add the post to the posts list
        this->posts.append(post_ui);
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

    // Update the video widget size
    video_widget->setGeometry(
      2 + 12, 2, parent_width - 24 - 4, parent_height - 4);

    // Set rounded mask on the video widget
    QPainterPath* painter_path = new QPainterPath();
    painter_path->addRoundedRect(
      QRect(0, 0, parent_width - 24 - 4, parent_height - 4),
      frame_radius,
      frame_radius);
    video_widget->setMask(painter_path->toFillPolygon().toPolygon());
};

void
FeedPostWindow::resizePosts(int parent_width, int parent_height)
{
    // Loop through the posts
    for (PostUi post : this->posts)
    {
        // Get the frame
        QFrame* frame = post.frame;

        // Update the frame size
        frame->setFixedSize(parent_width, parent_width * 5 / 4);

        // Update the video widget size and mask
        this->resizeFrameVideoWidget(
          frame->width(), frame->height(), frame, post.video_widget);
    };
};

void
FeedPostWindow::resizeScrollArea(int parent_width, int parent_height)
{
    // Get header size
    int header_height = this->header->height();

    // Update the scroll area size
    this->scroll_area->setFixedSize(parent_width,
                                    parent_height - header_height);
};

void
FeedPostWindow::resizeEvent(QResizeEvent* event)
{
    // Resize the scroll area
    this->resizeScrollArea(event->size().width(), event->size().height());

    // Resize the posts
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