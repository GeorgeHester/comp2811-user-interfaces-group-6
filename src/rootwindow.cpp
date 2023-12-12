#include "rootwindow.h"

RootWindow::RootWindow(QWidget* parent)
  : QMainWindow(parent)
{
    // Load in the font resource file
    Resource::import(QString(":/PlusJakartaSans Variable"));

    // Load in the different display mode style sheets
    this->qss_light_mode = Resource::load(QString(":/ui/style/light"));
    this->qss_dark_mode = Resource::load(QString(":/ui/style/dark"));
    this->qss_light_high_contrast_mode =
      Resource::load(QString(":/ui/style/light-high-contrast"));
    this->qss_dark_high_contrast_mode =
      Resource::load(QString(":/ui/style/dark-high-contrast"));

    // Set the current display mode based off of the user settings
    this->updateDisplayMode(
      (DisplayMode)SettingsHandler::getValue("display_mode", DisplayMode::Dark)
        .toInt());

    // Set the current font size
    this->updateFontSizeScale(
      SettingsHandler::getValue("font_size_scale", 1.0).toDouble());

    // Create the central layout for the main window
    QBoxLayout* central_layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    central_layout->setMargin(0);
    central_layout->setSpacing(0);

    // Create the central widget to store the layout and main window content
    QWidget* central_widget = new QWidget(this);
    central_widget->setLayout(central_layout);

    // Create the stacked widget which will store the different windows
    this->stacked_widget = new QStackedWidget(this);

    // Create the capture window widget
    this->capture_window = new CaptureWindow(this);
    this->stacked_widget->addWidget(this->capture_window);

    // Create the settings window widget
    this->settings_window = new SettingsWindow(this);
    this->stacked_widget->addWidget(this->settings_window);

    // Create the feed window widget
    this->feed_window = new FeedWindow(this);
    this->stacked_widget->addWidget(this->feed_window);

    // Create the post window widget
    this->post_window = new PostWindow(this);
    this->stacked_widget->addWidget(this->post_window);

    // Add the base items to the central layout
    central_layout->addWidget(this->stacked_widget);

    // Set the main windows central widget and object name
    this->setCentralWidget(central_widget);
    this->setObjectName(QString("MainWindow"));

    // Set the current window
    this->stacked_widget->setCurrentIndex(Window::Feed);

    // Connect the window updated listener
    // connect(footer,
    //        &Footer::selectedWindowUpdated,
    //        [=](int index)
    //        {
    //            this->stacked_widget->setCurrentIndex(index);
    //        });

    // Connect the display mode updated listener
    connect(this->settings_window,
            &SettingsWindow::displayModeUpdated,
            [this](DisplayMode display_mode)
            {
                this->updateDisplayMode(display_mode);
            });

    // Connect the font size scale updated listener
    connect(this->settings_window,
            &SettingsWindow::fontSizeScaleUpdated,
            [this](double scale)
            {
                this->updateFontSizeScale(scale);
            });

    // Connect for the window updated from feed window
    connect(this->feed_window,
            &FeedWindow::currentWindowUpdated,
            [this](Window to, Window from)
            {
                this->updateCurrentWindow(to, from);
            });

    // Connect for the window updated from settings window
    connect(this->settings_window,
            &SettingsWindow::currentWindowUpdated,
            [this](Window to, Window from)
            {
                this->updateCurrentWindow(to, from);
            });

    // Connect for the window updated from capture window
    connect(this->capture_window,
            &CaptureWindow::currentWindowUpdated,
            [this](Window to, Window from)
            {
                this->updateCurrentWindow(to, from);
            });

    // Connect for the window updated from post window
    connect(this->post_window,
            &PostWindow::currentWindowUpdated,
            [this](Window to, Window from)
            {
                this->updateCurrentWindow(to, from);
            });

    // Store::post_file_name =
    // "file:///Users/george/university/modules/comp2811/vreal/working/test.mp4";
    // this->updateCurrentWindow(Window::PostScreen, Window::Settings);
};

void
RootWindow::updateCurrentWindow(Window to, Window from)
{
    if (to == Window::Unknown)
    {
        this->stacked_widget->setCurrentIndex(this->previous_window);
        if (to == Window::PostScreen) this->post_window->refresh();
        this->stacked_widget->currentWidget()->update();
        this->previous_window = from;
        return;
    };

    this->stacked_widget->setCurrentIndex(to);
    if (to == Window::PostScreen) this->post_window->refresh();
    this->stacked_widget->currentWidget()->update();
    this->previous_window = from;
};

void
RootWindow::updateDisplayMode(DisplayMode display_mode)
{
    // Set the new display mode value in the user settings
    SettingsHandler::setValue("display_mode", display_mode);

    // Update the root style sheet
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

    this->updateFontSizeScale(
      SettingsHandler::getValue("font_size_scale", 1.0).toDouble());
};

void
RootWindow::updateFontSizeScale(double scale)
{
    // Set the new font size scale in the user settings
    SettingsHandler::setValue("font_size_scale", scale);

    QString* copy_style_sheet;
    QString* original_style_sheet;

    switch (
      (DisplayMode)SettingsHandler::getValue("display_mode", DisplayMode::Dark)
        .toInt())
    {
        case Light:
            copy_style_sheet = new QString(this->qss_light_mode);
            original_style_sheet = new QString(this->qss_light_mode);
            break;
        case Dark:
            copy_style_sheet = new QString(this->qss_dark_mode);
            original_style_sheet = new QString(this->qss_dark_mode);
            break;
        case LightHighContrast:
            copy_style_sheet = new QString(this->qss_light_high_contrast_mode);
            original_style_sheet =
              new QString(this->qss_light_high_contrast_mode);

            break;
        case DarkHighContrast:
            copy_style_sheet = new QString(this->qss_dark_high_contrast_mode);
            original_style_sheet =
              new QString(this->qss_dark_high_contrast_mode);
            break;
    };

    qsizetype start_index;
    qsizetype end_index;
    qsizetype copy_offset = 0;
    qsizetype original_offset = 0;

    while ((start_index = copy_style_sheet->indexOf(QString("font-size:"),
                                                    copy_offset)) != -1)
    {
        if ((end_index =
               copy_style_sheet->indexOf(QString("pt;"), copy_offset)) == -1)
            continue;

        QString font_size_string = copy_style_sheet->mid(
          start_index + QString("font-size:").length(),
          end_index - start_index - QString("font-size:").length());
        QString new_font_size_string =
          QString::number((int)round(font_size_string.toInt() * scale));

        original_style_sheet->replace(original_offset + start_index +
                                        QString("font-size:").length(),
                                      font_size_string.length(),
                                      new_font_size_string);

        original_offset +=
          new_font_size_string.length() - font_size_string.length();
        copy_offset = end_index + QString("pt;").length();
    };

    this->setStyleSheet(*original_style_sheet);
};