#include "./faviconManager.hpp"
#include <QtNetwork>
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>
#include "persistence/persistence.hpp"

namespace Network
{
    FaviconManager::FaviconManager(QObject *parent)
        : QObject(parent)
    {
    }

    FaviconManager *FaviconManager::getInstance()
    {
        static FaviconManager instance;
        return &instance;
    }

    void FaviconManager::requestFavicon(const QString &url) const
    {
        const QFileInfo fileInfo(url);
        const QString suffix = fileInfo.suffix();
        const QString dataDirPath = Persistence::Persistence::getDataDirPath();
        const QString faviconsDirPath = QString("%1/favicons").arg(dataDirPath);
        Persistence::Persistence::checkDir(faviconsDirPath);
        const QString fileName = QString("%1/%2.%3").arg(faviconsDirPath).arg(QCryptographicHash::hash(url.toUtf8(), QCryptographicHash::Md5).toHex()).arg(suffix);
        QFile file(fileName);
        if (file.exists())
        {
            emit faviconReady(url, fileName);
        }
        else
        {
            downloadFavicon(url, fileName);
        }
    }

    void FaviconManager::downloadFavicon(const QString &url, const QString &fileName) const
    {
        QNetworkAccessManager *const manager = new QNetworkAccessManager();
        QNetworkRequest request;
        request.setUrl(QUrl(url));
        QNetworkReply *const reply = manager->get(request);
        connect(reply, &QNetworkReply::finished, [=, this]() {
            if (reply->error() == QNetworkReply::NoError)
            {
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly))
                {
                    file.write(reply->readAll());
                    file.close();
                    emit faviconReady(url, fileName);
                }
            }
            reply->deleteLater();
            manager->deleteLater();
        });
        connect(reply, &QNetworkReply::errorOccurred, [=](QNetworkReply::NetworkError code) {
            manager->deleteLater();
        });
    }
} // namespace Network
