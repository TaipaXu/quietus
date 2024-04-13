#include "./common.hpp"
#include <QApplication>
#include <QUrl>
#include <QUuid>
#include "appConfig.hpp"

namespace Util
{
    Common::Common(QObject *parent)
        : QObject(parent)
    {
    }

    QString Common::getUuid()
    {
        return QUuid::createUuid().toString();
    }

    bool Common::isValidUrl(const QString &url)
    {
        QUrl qUrl(url);
        return qUrl.isValid() && (qUrl.scheme() == "http" || qUrl.scheme() == "https");
    }
} // namespace Util
