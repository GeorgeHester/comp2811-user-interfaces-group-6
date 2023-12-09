#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget* parent)
  : QWidget(parent)
{

    this->setObjectName(QString("SettingsWindow"));
    this->setSizePolicy(QSizePolicy::Policy::Expanding,
                        QSizePolicy::Policy::Expanding);
    // this->setFixedWidth(this->parentWidget()->width());

    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    // QLabel* debug_label = new QLabel(this);
    // debug_label->setText(QString::number(parent_geometry.height()));
    // layout->addWidget(debug_label);

    Header* header = new Header();
    layout->addWidget(header);

    this->display_mode_dropdown = new QComboBox(this);
    this->display_mode_dropdown->setObjectName(QString("DisplayModeDropdown"));
    this->display_mode_dropdown->addItem("Light", DisplayMode::Light);
    this->display_mode_dropdown->addItem("Dark", DisplayMode::Dark);
    this->display_mode_dropdown->addItem("Light High Contrast",
                                         DisplayMode::LightHighContrast);
    this->display_mode_dropdown->addItem("Dark High Contrast",
                                         DisplayMode::DarkHighContrast);
    this->display_mode_dropdown->setCurrentIndex(
      SettingsHandler::getValue(QString("display_mode"), DisplayMode::Dark)
        .toInt());
    layout->addWidget(display_mode_dropdown);
    SettingsWindow::updateDisplayModeDropdownWidth();

    this->connect(this->display_mode_dropdown,
                  QOverload<int>::of(&QComboBox::currentIndexChanged),
                  this,
                  &SettingsWindow::updateDisplayModeDropdownWidth);

    this->connect(this->display_mode_dropdown,
                  QOverload<int>::of(&QComboBox::currentIndexChanged),
                  [=](int index)
                  {
                      emit displayModeUpdated((DisplayMode)index);
                  });
};

void
SettingsWindow::updateDisplayModeDropdownWidth()
{
    this->display_mode_dropdown->setFixedWidth(
      this->display_mode_dropdown->sizeHint().width());
};

void
SettingsWindow::paintEvent(QPaintEvent*)
{
    QStyleOption style_option;
    style_option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &style_option, &painter, this);
};