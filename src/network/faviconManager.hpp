#pragma once

#include <QObject>

namespace Network
{
    class FaviconManager : public QObject
    {
        Q_OBJECT

    public:
        FaviconManager(const FaviconManager &) = delete;
        FaviconManager(FaviconManager &&) = delete;
        FaviconManager &operator=(const FaviconManager &) = delete;
        FaviconManager &operator=(FaviconManager &&) = delete;
        static FaviconManager *getInstance();
        ~FaviconManager() = default;

        Q_INVOKABLE void requestFavicon(const QString &url) const;

    signals:
        void faviconReady(const QString &url, const QString &fileName) const;

    private:
        FaviconManager(QObject *parent = nullptr);

    private:
        void downloadFavicon(const QString &url, const QString &fileName) const;
    };
} // namespace Network
