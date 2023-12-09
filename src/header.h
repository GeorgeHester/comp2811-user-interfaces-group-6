#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>

class Header : public QWidget
{
    Q_OBJECT

  public:
    Header(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent*);
};

#endif // HEADER_H
