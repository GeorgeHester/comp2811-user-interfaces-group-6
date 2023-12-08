#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QStackedLayout>

class Footer : public QWidget
{
    Q_OBJECT

  public:
    QPushButton* feed_window_button = NULL;
    QPushButton* capture_window_button = NULL;
    QStackedLayout* stacked_layout = NULL;

    Footer(QStackedLayout* stacked_layout)
    {
        this->stacked_layout = stacked_layout;
        this->feed_window_button = new QPushButton("Capture Window", this);
        this->capture_window_button = new QPushButton("Settings Window", this);

        QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight);

        layout->addWidget(this->feed_window_button);
        layout->addWidget(this->capture_window_button);

        this->setLayout(layout);

        connect(this->feed_window_button,
                &QPushButton::clicked,
                [this]()
                {
                    this->onButtonClicked(0, this->stacked_layout);
                });

        connect(this->capture_window_button,
                &QPushButton::clicked,
                [this]()
                {
                    this->onButtonClicked(1, this->stacked_layout);
                });
    };

  protected:
    void onButtonClicked(int index, QStackedLayout* layout)
    {
        if (layout == NULL) return;
        if (layout->count() <= index) return;
        if (index < 0) return;

        layout->setCurrentIndex(index);
    }
};

#endif // FOOTER_H
