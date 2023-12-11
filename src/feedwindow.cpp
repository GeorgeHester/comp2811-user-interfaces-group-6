#include "feedwindow.h"

FeedWindow::FeedWindow(QWidget* parent)
  : QWidget(parent)
{
    /*QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    Header* header = new Header(this);
    layout->addWidget(header);

    QMediaPlayer* player = new QMediaPlayer(this);
    QVideoWidget* video = new QVideoWidget(this);
    layout->addWidget(video);

    player->setVideoOutput(video);

    video->setGeometry(0, 0, 1000, 1000);
    video->setVisible(true);
    video->show();

    player->setMedia(
      QUrl::fromLocalFile("/Users/george/university/modules/comp2811/vreal/src/"
                          "static/video/post-03.mp4"));
    player->play();

    connect(player,
            QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
            [player](QMediaPlayer::Error error)
            {
                qDebug() << "Error: " << player->errorString();
            });*/

    // Create base layout of window
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    // Add header to window
    this->header = new Header("Settings", this);
    layout->addWidget(this->header);

    // Create scroll area to store the posts
    this->scroll_area = new QScrollArea(this);
    this->scroll_area->setObjectName("FeedWindowScrollArea");
    this->scroll_area->setHorizontalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->scroll_area->setVerticalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    this->scroll_area->setWidgetResizable(true);
    this->scroll_area->setAlignment(Qt::AlignTop);

    // Create a scroll area widget to hold the area contents
    QWidget* scroll_area_widget = new QWidget(scroll_area);
    this->scroll_area->setWidget(scroll_area_widget);

    // Create the layout for the scroll area widget
    QBoxLayout* scroll_area_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, scroll_area_widget);
    scroll_area_layout->setAlignment(Qt::AlignTop);
    scroll_area_layout->setMargin(0);
    scroll_area_layout->setSpacing(0);
    scroll_area_widget->setLayout(scroll_area_layout);

    for (int i = 0; i < 10; i++)
    {
        QFrame* frame = new QFrame(scroll_area_widget);
        frame->setObjectName("FeedWindowScrollAreaFrame");
        frame->setFixedSize(1000, 1000);

        this->frames.append(frame);
        scroll_area_layout->addWidget(frame);
    };

    // Connect handler for header navigation clicked
    connect(this->header,
            &Header::rightButtonClicked,
            [this]()
            {
                emit currentWindowUpdated(Window::Settings, Window::Feed);
            });
};

void
FeedWindow::addPost(){

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
FeedWindow::resizeFrames(int scroll_area_width, int scroll_area_height)
{
    for (QFrame* frame : this->frames)
    {
        // Update the size for the frame
        frame->setFixedSize(scroll_area_width - 14,
                            (scroll_area_width - 14) * 5 / 4);
    };
};

void
FeedWindow::resizeEvent(QResizeEvent* event)
{
    this->resizeScrollArea(event->size().width(), event->size().height());
    this->resizeFrames(this->scroll_area->width(), this->scroll_area->height());
    // this->paintCameraViewfinder(event->size().width(),
    // event->size().height());

    /*for (QFrame* frame : this->frames)
    {

    };*/

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