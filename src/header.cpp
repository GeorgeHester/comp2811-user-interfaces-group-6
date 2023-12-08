#include "header.h"

Header::Header()
  : QWidget()
{
    this->setObjectName("Header");
    this->setFixedHeight(48);

    QBoxLayout* box_layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    box_layout->setMargin(0);
    box_layout->setSpacing(0);

    this->setLayout(box_layout);

    QFont font;
    font.setFamily("Plus Jakarta Sans");
    font.setWeight(QFont::Bold);
    font.setPointSize(18);

    QLabel* logo_label = new QLabel();
    logo_label->setFont(font);
    logo_label->setText(QString::fromUtf8("VReal"));
    logo_label->setAlignment(Qt::AlignCenter);
    logo_label->setStyleSheet(QString::fromUtf8("QLabel{color:#F7EBE8}"));

    box_layout->addWidget(logo_label);
};