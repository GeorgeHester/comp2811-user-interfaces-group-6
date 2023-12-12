#include "feedwindow.h"

FeedWindow::FeedWindow(QWidget* parent)
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

    // Create a scroll area widget to hold the area contents
    this->scroll_area_widget = new QWidget(scroll_area);
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
                emit currentWindowUpdated(Window::Settings, Window::Feed);
            });
};

void
FeedWindow::paintPosts()
{
    this->blanks.clear();
    this->posts.clear();

    for (Post post : Store::posts)
    {
        QWidget* post_header = new QWidget(this->scroll_area_widget);
        post_header->setObjectName("FeedWindowScrollAreaPostHeader");
        this->scroll_area_layout->addWidget(post_header);

        QBoxLayout* post_header_layout =
          new QBoxLayout(QBoxLayout::Direction::LeftToRight, post_header);
        post_header_layout->setSpacing(0);

        QLabel* post_header_username_label =
          new QLabel(this->scroll_area_widget);
        post_header_username_label->setObjectName(
          "FeedWindowScrollAreaPostHeaderLabel");
        post_header_username_label->setAlignment(Qt::AlignLeft);
        post_header_username_label->setText(post.username);
        post_header_layout->addWidget(post_header_username_label);

        QLabel* post_header_time_label = new QLabel(this->scroll_area_widget);
        post_header_time_label->setObjectName(
          "FeedWindowScrollAreaPostHeaderLabel");
        post_header_time_label->setAlignment(Qt::AlignRight);
        post_header_time_label->setText(post.post_time);
        post_header_layout->addWidget(post_header_time_label);

        QFrame* post_frame = new QFrame(this->scroll_area_widget);
        post_frame->setObjectName("FeedWindowScrollAreaFrame");
        post_frame->setFixedSize(INT_MAX, INT_MAX);

        if (Store::feed_mode == FeedMode::PrePost)
        {
            QBoxLayout* post_frame_layout =
              new QBoxLayout(QBoxLayout::Direction::TopToBottom, post_frame);
            post_frame_layout->setAlignment(Qt::AlignCenter);
            post_frame_layout->setMargin(0);
            post_frame_layout->setSpacing(0);

            QPushButton* post_button =
              new QPushButton("Post VReal", post_frame);
            post_frame_layout->addWidget(post_button);

            connect(post_button,
                    &QPushButton::clicked,
                    [this]()
                    {
                        emit currentWindowUpdated(Window::Capture,
                                                  Window::Feed);
                    });

            PostBlank post_blank;
            post_blank.frame = post_frame;

            this->blanks.append(post_blank);
            this->scroll_area_layout->addWidget(post_frame);
            continue;
        };

        if (Store::feed_mode == FeedMode::PostPost)
        {
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
            this->scroll_area_layout->addWidget(post_frame);
            continue;
        };
    };
};

void
FeedWindow::resizeScrollArea(int window_width, int window_height)
{
    // Get new sizes
    int header_height = this->header->height();

    // Update the geometry for the scroll area
    this->scroll_area->setGeometry(
      0, header_height, window_width, window_height - header_height);
};

void
FeedWindow::resizePosts(int parent_width, int parent_height)
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
FeedWindow::resizePostBlanks(int parent_width, int parent_height)
{
    for (int index = 0; index < this->blanks.length(); index++)
    {
        QFrame* frame = this->blanks[index].frame;

        // Update the size for the frame
        frame->setFixedSize(parent_width - 14, (parent_width - 14) * 5 / 4);
    };
};

void
FeedWindow::resizeFrameVideoWidget(int parent_width,
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
FeedWindow::resizeEvent(QResizeEvent* event)
{
    // Handle resizing the scroll area
    this->resizeScrollArea(event->size().width(), event->size().height());

    // Handle resizing the posts
    this->resizePosts(this->scroll_area->width(), this->scroll_area->height());

    // Handle resizing the post blanks
    this->resizePostBlanks(this->scroll_area->width(),
                           this->scroll_area->height());

    QWidget::resizeEvent(event);
};

void
FeedWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};