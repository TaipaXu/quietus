#include "./quietus.hpp"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QMenu>
#include <QIcon>
#include "persistence/website.hpp"
#include "models/website.hpp"
#include "network/faviconManager.hpp"

namespace Widget
{
    Quietus::Quietus(const std::shared_ptr<Model::Website> &website, QObject *parent)
        : QObject(parent), website{website}, tray{nullptr}, trayMenu{nullptr}, engine{nullptr}
    {
        websitePersistence = Persistence::Website::getInstance();

        createTray();
        createEngine();
    }

    Quietus::~Quietus()
    {
        trayMenu->deleteLater();
        engine->deleteLater();
    }

    const std::shared_ptr<Model::Website> &Quietus::getWebsite() const
    {
        return website;
    }

    void Quietus::createTray()
    {
        tray = new QSystemTrayIcon(this);
        connect(tray, &QSystemTrayIcon::activated, this, &Quietus::onTrayMenuActivated);
        tray->setToolTip(tr("Quietus"));
        tray->setIcon(QIcon(":/images/icon"));
        tray->show();

        trayMenu = new QMenu();

        QAction *newInstanceAction = new QAction(tr("New one"), this);
        connect(newInstanceAction, &QAction::triggered, this, &Quietus::newInstance);
        trayMenu->addAction(newInstanceAction);

        QAction *removeMeAction = new QAction(tr("Remove me"), this);
        connect(removeMeAction, &QAction::triggered, this, &Quietus::removeInstance);
        trayMenu->addAction(removeMeAction);

        trayMenu->addSeparator();

        const QIcon exitIcon{QIcon::fromTheme("application-exit")};
        QAction *exitAction{trayMenu->addAction(exitIcon, tr("E&xit"), this, &QApplication::quit)};

#ifndef Q_OS_MACOS
        tray->setContextMenu(trayMenu);
#endif

        connect(Network::FaviconManager::getInstance(), &Network::FaviconManager::faviconReady, this, &Quietus::onFaviconReady);
    }

    void Quietus::createEngine()
    {
        engine = new QQmlApplicationEngine();
        engine->setInitialProperties({
            {"id", website->getId()},
            {"name", website->getName()},
            {"favicon", website->getFavicon()},
            {"url", website->getUrl()},
        });
        engine->load("qrc:/widgets/Window.qml");
        QObject *root = engine->rootObjects().first();
        QObject::connect(root, SIGNAL(home()), this, SLOT(onHome()));
        QObject::connect(root, SIGNAL(nameModified(QString)), this, SLOT(onNameChanged(QString)));
        QObject::connect(root, SIGNAL(faviconModified(QString)), this, SLOT(onIconChanged(QString)));
        QObject::connect(root, SIGNAL(urlModified(QString)), this, SLOT(onUrlChanged(QString)));
    }

    void Quietus::onTrayMenuActivated(QSystemTrayIcon::ActivationReason reason) const
    {
        switch (reason)
        {
        case QSystemTrayIcon::Trigger:
        {
            if (engine->rootObjects().first()->property("visible").toBool())
            {
                engine->rootObjects().first()->setProperty("visible", false);
            }
            else
            {
                engine->rootObjects().first()->setProperty("x", QCursor::pos().x() - 150);
                engine->rootObjects().first()->setProperty("y", QCursor::pos().y() - 500);
                engine->rootObjects().first()->setProperty("visible", true);
            }
            break;
        }

        case QSystemTrayIcon::DoubleClick:
        {
            break;
        }

        case QSystemTrayIcon::MiddleClick:
        {
            break;
        }

        case QSystemTrayIcon::Context:
        {
#ifdef Q_OS_MACOS
            engine->rootObjects().first()->setProperty("visible", false);
            trayMenu->popup(QCursor::pos());
#endif
            break;
        }

        default:
            break;
        }
    }

    void Quietus::onFaviconReady(const QString &url, const QString &fileName) const
    {
        if (faviconUrl == url)
        {
            tray->setIcon(QIcon(fileName));
        }
    }

    void Quietus::onHome()
    {
        faviconUrl.clear();
        tray->setIcon(QIcon(":/images/icon"));
        website->clear();
        websitePersistence->updateWebsites();
    }

    void Quietus::onNameChanged(const QString &title) const
    {
        website->setName(title);
        websitePersistence->updateWebsites();
    }

    void Quietus::onIconChanged(const QString &url)
    {
        if (faviconUrl != url)
        {
            faviconUrl = url;
            Network::FaviconManager::getInstance()->requestFavicon(url);
            website->setFavicon(url);
            websitePersistence->updateWebsites();
        }
    }

    void Quietus::onUrlChanged(const QString &url) const
    {
        website->setUrl(url);
        websitePersistence->updateWebsites();
    }
} // namespace Widget
