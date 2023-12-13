#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget* parent)
  : QWidget(parent)
{
    // Create the layout for the widget
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);

    // Create a header
    Header* header = new Header("Back", this);
    layout->addWidget(header);

    // Create a label
    QLabel* display_mode_combo_box_label = new QLabel(this);
    display_mode_combo_box_label->setObjectName("SettingsWindowItemLabel");
    display_mode_combo_box_label->setText("Display Mode");
    layout->addWidget(display_mode_combo_box_label);

    // Create a combo box
    QComboBox* display_mode_combo_box = new QComboBox(this);
    display_mode_combo_box->setObjectName("SettingsWindowComboBox");
    display_mode_combo_box->addItem("Light", DisplayMode::Light);
    display_mode_combo_box->addItem("Dark", DisplayMode::Dark);
    display_mode_combo_box->addItem("Light High Contrast",
                                    DisplayMode::LightHighContrast);
    display_mode_combo_box->addItem("Dark High Contrast",
                                    DisplayMode::DarkHighContrast);
    display_mode_combo_box->setCurrentIndex(
      SettingsHandler::getValue("display_mode", DisplayMode::Dark).toInt());
    layout->addWidget(display_mode_combo_box);

    // Create a label
    QLabel* font_size_scale_slider_label = new QLabel(this);
    font_size_scale_slider_label->setObjectName("SettingsWindowItemLabel");
    font_size_scale_slider_label->setText("Font Size Scale");
    layout->addWidget(font_size_scale_slider_label);

    // Create a slider
    QSlider* font_size_scale_slider =
      new QSlider(Qt::Orientation::Horizontal, this);
    font_size_scale_slider->setObjectName("SettingsWindowSlider");
    font_size_scale_slider->setRange(5, 20);
    font_size_scale_slider->setSingleStep(1);
    font_size_scale_slider->setValue(static_cast<int>(
      SettingsHandler::getValue("font_size_scale", 1.0).toDouble() * 10.0));
    layout->addWidget(font_size_scale_slider);

    // Create a reset button
    QPushButton* reset_button = new QPushButton("Reset", this);
    reset_button->setObjectName("SettingsWindowResetButton");
    layout->addWidget(reset_button);

    // Connect handler for combo box index changed
    this->connect(display_mode_combo_box,
                  QOverload<int>::of(&QComboBox::currentIndexChanged),
                  [this](int index)
                  {
                      emit displayModeUpdated((DisplayMode)index);
                  });

    // Connect handler for slider value changed
    this->connect(font_size_scale_slider,
                  &QSlider::valueChanged,
                  [this](int value)
                  {
                      emit fontSizeScaleUpdated(static_cast<double>(value) /
                                                10.0);
                  });

    // Connect handler for reset button clicked
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
SettingsWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};