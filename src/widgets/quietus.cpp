#include "./quietus.hpp"
#include <QApplication>
#include <QDesktopServices>
#ifndef Q_OS_MACOS
#include <QScreen>
#endif
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMenu>
#include <QIcon>
#include "models/website.hpp"
#include "persistence/website.hpp"
#include "links/favorite.hpp"
#include "network/faviconManager.hpp"
#include "appConfig.hpp"

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

        QAction *adjustWindowAction = new QAction(tr("Adjust window"), this);
        connect(adjustWindowAction, &QAction::triggered, this, &Quietus::onAdjustWindow);
        trayMenu->addAction(adjustWindowAction);

        trayMenu->addSeparator();

        QMenu *aboutMenu = new QMenu(tr("About"));
        QAction *aboutMeAction = new QAction(tr("About me"), this);
        connect(aboutMeAction, &QAction::triggered, []() {
            QDesktopServices::openUrl(QUrl(ORGANIZATION_DOMAIN));
        });
        aboutMenu->addAction(aboutMeAction);
        QAction *projectDomainAction = new QAction(tr("Project domain"), this);
        connect(projectDomainAction, &QAction::triggered, []() {
            QDesktopServices::openUrl(QUrl(PROJECT_DOMAIN));
        });
        aboutMenu->addAction(projectDomainAction);
        QAction *bugReportAction = new QAction(tr("Bug report"), this);
        connect(bugReportAction, &QAction::triggered, []() {
            QDesktopServices::openUrl(QUrl(PROJECT_ISSUES_DOMAIN));
        });
        aboutMenu->addAction(bugReportAction);
        trayMenu->addMenu(aboutMenu);

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
        engine->rootContext()->setContextProperty("FavoriteLink", Link::Favorite::getInstance());
        engine->setInitialProperties({
            {"name", website->getName()},
            {"favicon", website->getFavicon()},
            {"url", website->getUrl()},
            {"mobileMode", website->isMobileMode()},
        });
        engine->load("qrc:/widgets/Window.qml");
        if (website->hasSizeAndPosition())
        {
            setWidgetSizeAndPositionWidthStoredData();
        }
        QObject *root = engine->rootObjects().first();
        QObject::connect(root, SIGNAL(home()), this, SLOT(onHome()));
        QObject::connect(root, SIGNAL(nameModified(QString)), this, SLOT(onNameChanged(QString)));
        QObject::connect(root, SIGNAL(faviconModified(QString)), this, SLOT(onIconChanged(QString)));
        QObject::connect(root, SIGNAL(urlModified(QString)), this, SLOT(onUrlChanged(QString)));
        QObject::connect(root, SIGNAL(mobileModeModified(bool)), this, SLOT(onMobileModeChanged(bool)));
        QObject::connect(root, SIGNAL(adjustDone(int, int, int, int)), this, SLOT(onAdjustDone(int, int, int, int)));
    }

    void Quietus::setWidgetPosition() const
    {
        engine->rootObjects().first()->setProperty("x", QCursor::pos().x() - 150);
#ifdef Q_OS_MACOS
        engine->rootObjects().first()->setProperty("y", 0);
#else
        engine->rootObjects().first()->setProperty("y", QApplication::primaryScreen()->size().height() - engine->rootObjects().first()->property("height").toInt());
#endif
    }

    void Quietus::setWidgetSizeAndPositionWidthStoredData() const
    {
        engine->rootObjects().first()->setProperty("width", website->getWidth());
        engine->rootObjects().first()->setProperty("height", website->getHeight());
        engine->rootObjects().first()->setProperty("x", website->getX());
        engine->rootObjects().first()->setProperty("y", website->getY());
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
                if (website->hasSizeAndPosition())
                {
                    setWidgetSizeAndPositionWidthStoredData();
                }
                else
                {
                    setWidgetPosition();
                }
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

    void Quietus::onAdjustWindow() const
    {
        if (website->hasSizeAndPosition())
        {
            setWidgetSizeAndPositionWidthStoredData();
        }
        else
        {
            setWidgetPosition();
        }
        engine->rootObjects().first()->setProperty("visible", true);
        engine->rootObjects().first()->setProperty("adjusting", true);
    }

    void Quietus::onAdjustDone(int width, int height, int x, int y) const
    {
        website->setSizeAndPosition(width, height, x, y);
        websitePersistence->updateWebsites();
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

    void Quietus::onMobileModeChanged(bool isMobileMode) const
    {
        website->setMobileMode(isMobileMode);
        websitePersistence->updateWebsites();
    }
} // namespace Widget
