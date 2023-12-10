#include "header.h"

Header::Header(QWidget* parent)
  : QWidget(parent)
{
    this->setObjectName("Header");

    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
    layout->setMargin(0);
    layout->setSpacing(0);

    QLabel* logo_label = new QLabel(this);
    logo_label->setObjectName("HeaderLogo");
    logo_label->setText(QString("VReal"));
    logo_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(logo_label);

    this->setLayout(layout);
};

void
Header::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};