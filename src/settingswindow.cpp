#include "settingswindow.h"

SettingsWindow::SettingsWindow()
{
    QBoxLayout* layout =
      new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    layout->setAlignment(Qt::AlignTop);
    layout->setMargin(0);
    layout->setSpacing(0);
    this->setLayout(layout);

    Header* header = new Header();
    layout->addWidget(header);

    QFont font;
    font.setFamily("Plus Jakarta Sans");
    font.setWeight(QFont::Weight::DemiBold);
    font.setPointSize(14);

    this->display_mode_dropdown = new QComboBox(this);
    this->display_mode_dropdown->setFont(font);
    this->display_mode_dropdown->setFixedHeight(24);
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

    this->connect(this->display_mode_dropdown,
                  QOverload<int>::of(&QComboBox::currentIndexChanged),
                  [=](int index)
                  {
                      emit displayModeUpdated((DisplayMode)index);
                  });
};