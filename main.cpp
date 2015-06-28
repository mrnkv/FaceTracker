#include "views/setupview.h"
#include "controllers/basecontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("orgname");
    app.setOrganizationDomain("facetrcker.com");
    app.setApplicationName("FaceTracker");
    app.setApplicationVersion("0.0.1");

    BaseController ctrl;
    ctrl.createConnections();
    ctrl.startTimers();
    QObject::connect(&ctrl, &BaseController::quit, &app, &QApplication::quit);

    ctrl.start();
    QApplication::setQuitOnLastWindowClosed(false);
    return app.exec();
}
