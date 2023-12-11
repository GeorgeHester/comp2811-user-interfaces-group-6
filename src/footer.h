#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QStackedLayout>
#include <QStyleOption>
#include <QPainter>

class Footer : public QWidget
{
    Q_OBJECT

  public:
    Footer(QWidget* parent = nullptr)
      : QWidget(parent)
    {
        QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
        this->setLayout(layout);

        QPushButton* capture_window_button =
          new QPushButton("Capture Window", this);
        layout->addWidget(capture_window_button);

        QPushButton* settings_window_button =
          new QPushButton("Settings Window", this);
        layout->addWidget(settings_window_button);

        QPushButton* feed_window_button = new QPushButton("Feed Window", this);
        layout->addWidget(feed_window_button);

        connect(capture_window_button,
                &QPushButton::clicked,
                [this]()
                {
                    emit selectedWindowUpdated(0);
                });

        connect(settings_window_button,
                &QPushButton::clicked,
                [this]()
                {
                    emit selectedWindowUpdated(1);
                });

        connect(feed_window_button,
                &QPushButton::clicked,
                [this]()
                {
                    emit selectedWindowUpdated(2);
                });
    };

  signals:
    void selectedWindowUpdated(int index);

  protected:
    void paintEvent(QPaintEvent*) override
    {
        QStyleOption style_option;
        style_option.init(this);
        QPainter painter(this);
        style()->drawPrimitive(
          QStyle::PE_Widget, &style_option, &painter, this);
    };
};

#endif // FOOTER_H
