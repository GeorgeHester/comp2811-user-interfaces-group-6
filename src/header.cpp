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
};

Header::Header(QString right_button_text, QWidget* parent)
  : QWidget(parent)
{
    this->setObjectName("Header");

    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::LeftToRight, this);
    layout->setMargin(0);
    layout->setSpacing(0);

    QSpacerItem* spacer_left =
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(spacer_left);

    QLabel* logo_label = new QLabel(this);
    logo_label->setObjectName("HeaderLogo");
    logo_label->setText(QString("VReal"));
    logo_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(logo_label);

    QPushButton* right_button = new QPushButton(right_button_text, this);
    right_button->setFlat(true);
    layout->addWidget(right_button, 0, Qt::AlignRight);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
    layout->setStretch(2, 1);

    connect(right_button,
            &QPushButton::clicked,
            [this]()
            {
                emit rightButtonClicked();
            });
};

void
Header::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};