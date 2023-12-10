#include <QApplication>

#include "rootwindow.h"

int
main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    RootWindow* root_window = new RootWindow();
    root_window->show();
    root_window->resize(320, 640);

    app.exec();
    return 0;
};
