#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget* parent)
  : QWidget(parent)
{
    this->setObjectName(QString("SettingsWindow"));

    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    Header* header = new Header("Back", this);
    layout->addWidget(header);

    QLabel* display_mode_combo_box_label = new QLabel(this);
    display_mode_combo_box_label->setObjectName(
      QString("SettingsWindowItemLabel"));
    display_mode_combo_box_label->setText(QString("Display Mode"));
    layout->addWidget(display_mode_combo_box_label);

    QComboBox* display_mode_combo_box = new QComboBox(this);
    display_mode_combo_box->setObjectName(QString("DisplayModeDropdown"));
    display_mode_combo_box->addItem("Light", DisplayMode::Light);
    display_mode_combo_box->addItem("Dark", DisplayMode::Dark);
    display_mode_combo_box->addItem("Light High Contrast",
                                    DisplayMode::LightHighContrast);
    display_mode_combo_box->addItem("Dark High Contrast",
                                    DisplayMode::DarkHighContrast);
    display_mode_combo_box->setCurrentIndex(
      SettingsHandler::getValue(QString("display_mode"), DisplayMode::Dark)
        .toInt());
    layout->addWidget(display_mode_combo_box);

    QLabel* font_size_scale_slider_label = new QLabel(this);
    font_size_scale_slider_label->setObjectName(
      QString("SettingsWindowItemLabel"));
    font_size_scale_slider_label->setText(QString("Font Size Scale"));
    layout->addWidget(font_size_scale_slider_label);

    QSlider* font_size_scale_slider =
      new QSlider(Qt::Orientation::Horizontal, this);
    font_size_scale_slider->setRange(5, 20);
    font_size_scale_slider->setSingleStep(1);
    font_size_scale_slider->setValue(static_cast<int>(
      SettingsHandler::getValue("font_size_scale", 1.0).toDouble() * 10.0));
    layout->addWidget(font_size_scale_slider);

    QPushButton* reset_button = new QPushButton("Reset", this);
    reset_button->setObjectName(QString("SettingsWindowResetButton"));
    layout->addWidget(reset_button);

    this->connect(display_mode_combo_box,
                  QOverload<int>::of(&QComboBox::currentIndexChanged),
                  [=](int index)
                  {
                      emit displayModeUpdated((DisplayMode)index);
                  });

    this->connect(font_size_scale_slider,
                  &QSlider::valueChanged,
                  [=](int value)
                  {
                      emit fontSizeScaleUpdated(static_cast<double>(value) /
                                                10.0);
                  });

    this->connect(reset_button,
                  &QPushButton::clicked,
                  [this, display_mode_combo_box, font_size_scale_slider]()
                  {
                      // Reset the user interface
                      display_mode_combo_box->setCurrentIndex(
                        DisplayMode::Dark);
                      font_size_scale_slider->setValue(10);

                      // Update the values globally
                      emit displayModeUpdated(DisplayMode::Dark);
                      emit fontSizeScaleUpdated(1.0);
                  });

    // Connect handler for header navigation clicked
    connect(header,
            &Header::rightButtonClicked,
            [this]()
            {
                emit currentWindowUpdated(Window::Unknown, Window::Settings);
            });
};

void
SettingsWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
};

void
SettingsWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};