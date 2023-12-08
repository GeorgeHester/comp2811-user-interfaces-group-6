#include "rootwindow.h"

RootWindow::RootWindow()
  : QMainWindow()
{
    Resource::import(QString("PlusJakartaSans Variable"));

    this->qss_light_mode = Resource::load(QString(":/ui/style/light"));
    this->qss_dark_mode = Resource::load(QString(":/ui/style/dark"));
    this->qss_light_high_contrast_mode =
      Resource::load(QString(":/ui/style/light-high-contrast"));
    this->qss_dark_high_contrast_mode =
      Resource::load(QString(":/ui/style/dark-high-contrast"));

    QBoxLayout* vertical_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    vertical_layout->setMargin(0);
    vertical_layout->setSpacing(0);

    QWidget* central_widget = new QWidget;
    central_widget->setLayout(vertical_layout);

    QStackedLayout* stacked_layout = new QStackedLayout;
    stacked_layout->setMargin(0);
    stacked_layout->setSpacing(0);

    CaptureWindow* capture_window = new CaptureWindow;
    stacked_layout->addWidget(capture_window);

    SettingsWindow* settings_window = new SettingsWindow();
    stacked_layout->addWidget(settings_window);

    Footer* footer = new Footer(stacked_layout);

    vertical_layout->addLayout(stacked_layout);
    vertical_layout->addWidget(footer);

    this->setCentralWidget(central_widget);
    this->setObjectName(QString("MainWindow"));
    this->updateDisplayMode(DisplayMode::Dark);

    connect(settings_window,
            &SettingsWindow::displayModeUpdated,
            [=](DisplayMode display_mode)
            {
                this->updateDisplayMode(display_mode);
            });
};

void
RootWindow::updateDisplayMode(DisplayMode display_mode)
{
    switch (display_mode)
    {
        case Light:
            this->setStyleSheet(this->qss_light_mode);
            break;
        case Dark:
            this->setStyleSheet(this->qss_dark_mode);
            break;
        case LightHighContrast:
            this->setStyleSheet(this->qss_light_high_contrast_mode);
            break;
        case DarkHighContrast:
            this->setStyleSheet(this->qss_dark_high_contrast_mode);
            break;
    };
};