#include <QAbstractVideoSurface>
#include <QApplication>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QRect>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

bool
cameraAvailable()
{
    if (QCameraInfo::availableCameras().count() > 0) return true;
    return false;
};

int
main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow* window = new QMainWindow();
    window->setBaseSize(QSize(320, 640));
    window->show();

    QWidget* central_widget = new QWidget();
    window->setCentralWidget(central_widget);

    QVBoxLayout* vertical_layout = new QVBoxLayout();
    central_widget->setLayout(vertical_layout);

    ////
    QLabel* camera_available_label = new QLabel();
    vertical_layout->addWidget(camera_available_label);

    if (cameraAvailable() == true)
    {
        camera_available_label->setText(QString::fromUtf8("Camera Available"));
    }
    else
    {
        camera_available_label->setText(
          QString::fromUtf8("Camera Not Available"));
    };
    ////

    ////
    QList<QCameraInfo> camera_info_list = QCameraInfo::availableCameras();

    for (QCameraInfo& camera_info : camera_info_list)
    {
        QLabel* camera_info_label = new QLabel();
        camera_info_label->setText(camera_info.deviceName());
        vertical_layout->addWidget(camera_info_label);
    };
    ////

    if (camera_info_list.length() > 0)
    {
        QCameraViewfinder* viewfinder = new QCameraViewfinder();
        vertical_layout->addWidget(viewfinder);

        QCamera* camera = new QCamera(camera_info_list.at(0));
        camera->setViewfinder(viewfinder);
        camera->start();

        // QAbstractVideoSurface *video_surface = new
        // QAbstractVideoSurface(central_widget);
        // camera->setViewfinder(video_surface);
        //
        // camera->setViewfinder(viewfinder);
        // QLabel *camera_info_label = new QLabel();
        /*if (camera->isAvailable() == true) {
            camera_info_label->setText("Camera Working");
        } else {
            camera_info_label->setText("Camera Not Working");
        };
        vertical_layout->addWidget(camera_info_label);

        camera->start();*/
    };
    ////

    return app.exec();
};
