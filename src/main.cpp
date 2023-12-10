#include <QApplication>

#include "rootwindow.h"

int
main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    RootWindow* root_window = new RootWindow();
    root_window->resize(320, 640);
    root_window->show();

    double scale = 1.5;
    std::string scale_string = std::to_string(scale);
    QByteArray scale_byte_array =
      QByteArray(scale_string.c_str(), scale_string.length());

    qputenv("QT_SCALE_FACTOR", scale_byte_array);

    app.exec();
    return 0;
};
