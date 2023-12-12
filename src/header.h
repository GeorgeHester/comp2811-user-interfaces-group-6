#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QSpacerItem>
#include <QPaintEvent>

class Header : public QWidget
{
    Q_OBJECT

  public:
    Header(QWidget* parent = nullptr);
    Header(QString right_button_text, QWidget* parent = nullptr);

  signals:
    void rightButtonClicked();

  protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // HEADER_H
