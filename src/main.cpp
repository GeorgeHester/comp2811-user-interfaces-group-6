#include <QApplication>

#include "rootwindow.h"
#include "store.h"

int
main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Store::loadPosts();

    RootWindow* root_window = new RootWindow();
    root_window->show();
    root_window->setMinimumSize(320, 640);

    app.exec();
    return 0;
};
