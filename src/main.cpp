#include <QApplication>
#include <QIcon>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include "core.hpp"
#include "appConfig.hpp"

int main(int argc, char *argv[])
{
#ifdef __linux__
    QByteArray waylandDisplay = qgetenv("WAYLAND_DISPLAY");
    if (!waylandDisplay.isEmpty())
    {
        qputenv("QT_QPA_PLATFORM", QByteArray("xcb"));
    }
#endif

    QtWebEngineQuick::initialize();
    QApplication app(argc, argv);
    app.setOrganizationDomain(ORGANIZATION_DOMAIN);
    app.setApplicationVersion(PROJECT_VERSION);
    app.setApplicationName(PROJECT_NAME);
    app.setQuitOnLastWindowClosed(false);

    app.setWindowIcon(QIcon(":/images/icon"));

    Core core;

    const int result = app.exec();

    return result;
}
