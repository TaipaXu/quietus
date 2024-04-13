#pragma once

#include <memory>
#include <QSystemTrayIcon>

namespace Persistence
{
    class Website;
}

namespace Model
{
    class Website;
} // namespace Model

QT_BEGIN_NAMESPACE
class QQmlApplicationEngine;
QT_END_NAMESPACE

namespace Widget
{
    class Quietus : public QObject
    {
        Q_OBJECT

    public:
        explicit Quietus(const std::shared_ptr<Model::Website> &website, QObject *parent = nullptr);
        ~Quietus();

        const std::shared_ptr<Model::Website> &getWebsite() const;

    signals:
        void newInstance() const;
        void removeInstance() const;

    private:
        void createTray();
        void createEngine();

    private slots:
        void onTrayMenuActivated(QSystemTrayIcon::ActivationReason reason) const;
        void onFaviconReady(const QString &url, const QString &fileName) const;
        void onHome();
        void onNameChanged(const QString &title) const;
        void onIconChanged(const QString &url);
        void onUrlChanged(const QString &url) const;
        void onMobileModeChanged(bool isMobileMode) const;

    private:
        std::shared_ptr<Model::Website> website;
        Persistence::Website *websitePersistence;
        QSystemTrayIcon *tray;
        QMenu *trayMenu;
        QQmlApplicationEngine *engine;
        QString faviconUrl;
    };
} // namespace Widget
