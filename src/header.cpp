#include "header.h"

Header::Header(QWidget* parent)
  : QWidget(parent)
{
    this->setObjectName("Header");
    this->setFixedHeight(48);

    QBoxLayout* box_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    box_layout->setMargin(0);
    box_layout->setSpacing(0);

    this->setLayout(box_layout);

    QLabel* logo_label = new QLabel();
    logo_label->setObjectName("HeaderLogo");
    logo_label->setText(QString("VReal"));
    logo_label->setAlignment(Qt::AlignCenter);
    box_layout->addWidget(logo_label);
};

void
Header::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};