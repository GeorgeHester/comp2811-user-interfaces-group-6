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
    this->setLayout(layout);

    // Create a header with a back button
    this->header = new Header("Back", this);
    layout->addWidget(this->header);

    // Create a post button
    this->post_button = new QPushButton("Post", this);
    layout->addWidget(this->post_button);
};

void
PostWindow::resizeEvent(QResizeEvent* event)
{
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
