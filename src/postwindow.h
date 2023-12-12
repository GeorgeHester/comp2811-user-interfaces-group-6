#ifndef POSTWINDOW_H
#define POSTWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QBoxLayout>
#include <QPushButton>

#include "header.h"
#include "window.h"

class PostWindow : public QWidget
{
    Q_OBJECT

  public:
    PostWindow(QWidget* parent = nullptr);
    Header* header;
    QPushButton* post_button;

  signals:
    void currentWindowUpdated(Window to, Window from);

  protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
};

#endif // POSTWINDOW_H
