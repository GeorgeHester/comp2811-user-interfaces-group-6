#include "feedprewindow.h"

FeedPreWindow::FeedPreWindow(QWidget* parent)
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

    // Paint post blanks
    this->paintPosts();

    // Connect handler for header navigation clicked
    connect(this->header,
            &Header::rightButtonClicked,
            [this]()
            {
                emit currentWindowUpdated(Window::Settings, Window::FeedPre);
            });
};

void
FeedPreWindow::paintPosts()
{
    // Clear the current post blanks
    this->blanks.clear();

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
        // post_header_layout->setMargin(0);
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

        // Create a post blank frame
        QFrame* post_frame = new QFrame(this->scroll_area_widget);
        post_frame->setObjectName("FeedWindowScrollAreaFrame");
        post_frame->setFixedSize(0, 0);
        this->scroll_area_layout->addWidget(post_frame);

        // Create the layout for the post blank frame
        QBoxLayout* post_frame_layout =
          new QBoxLayout(QBoxLayout::Direction::TopToBottom, post_frame);
        post_frame_layout->setAlignment(Qt::AlignCenter);
        post_frame_layout->setMargin(0);
        post_frame_layout->setSpacing(0);

        // Create a post button
        QPushButton* post_button = new QPushButton("Post VReal", post_frame);
        post_frame_layout->addWidget(post_button);

        // Connect handler for post button clicked
        connect(post_button,
                &QPushButton::clicked,
                [this]()
                {
                    emit currentWindowUpdated(Window::Capture, Window::FeedPre);
                });

        // Create a post blank
        PostBlank post_blank;
        post_blank.frame = post_frame;

        // Add the blank to the blanks list
        this->blanks.append(post_blank);
    };
};

void
FeedPreWindow::resizePostBlanks(int parent_width, int parent_height)
{
    // Loop through the post blanks
    for (PostBlank post_blank : this->blanks)
    {
        // Get the frame
        QFrame* frame = post_blank.frame;

        // Update the frame size
        frame->setFixedSize(parent_width, parent_width * 5 / 4);
    };
};

void
FeedPreWindow::resizeScrollArea(int parent_width, int parent_height)
{
    // Get header size
    int header_height = this->header->height();

    // Update the scroll area size
    this->scroll_area->setFixedSize(parent_width,
                                    parent_height - header_height);
};

void
FeedPreWindow::resizeEvent(QResizeEvent* event)
{
    // Resize the scroll area
    this->resizeScrollArea(event->size().width(), event->size().height());

    // Resize the post blanks
    this->resizePostBlanks(this->scroll_area->width(),
                           this->scroll_area->height());

    QWidget::resizeEvent(event);
};

void
FeedPreWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};