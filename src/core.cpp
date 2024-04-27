#include "./core.hpp"
#include <QGuiApplication>
#include <QTranslator>
#include <QQmlEngine>
#include <QJSEngine>
#include "widgets/quietus.hpp"
#include "models/website.hpp"
#include "models/favorite.hpp"
#include "links/favorite.hpp"
#include "persistence/website.hpp"
#include "utils/common.hpp"

Core::Core()
{
    QTranslator *translator = new QTranslator(this);
    QLocale locale;
    if (locale.language() == QLocale::Chinese)
    {
        std::ignore = translator->load(":/i18n/zh_CN");
    }
    qApp->installTranslator(translator);

    qmlRegisterType<Util::Common>("utils", 1, 0, "Utils");
    qmlRegisterType<Model::Website>("model.website", 1, 0, "Website");
    qmlRegisterType<Model::FavoriteGroup>("model.favoriteGroup", 1, 0, "FavoriteGroup");
    qmlRegisterSingletonType(QUrl("qrc:/widgets/EventBus.qml"), "app.eventbus", 1, 0, "EventBus");
    QJSEngine::setObjectOwnership(Link::Favorite::getInstance(), QQmlEngine::CppOwnership);

    websitePersistence = Persistence::Website::getInstance();
    const std::list<std::shared_ptr<Model::Website>> websites = websitePersistence->getWebsites();
    if (websites.empty()) [[unlikely]]
    {
        onNewInstance();
    }
    else [[likely]]
    {
        for (auto &&website : websites)
        {
            createInstance(website);
        }
    }
}

void Core::createInstance(const std::shared_ptr<Model::Website> &website)
{
    Widget::Quietus *quietus = new Widget::Quietus(website, this);
    connect(quietus, &Widget::Quietus::newInstance, this, &Core::onNewInstance);
    connect(quietus, &Widget::Quietus::removeInstance, this, &Core::onRemoveInstance);
}

void Core::onNewInstance()
{
    const std::shared_ptr<Model::Website> website = std::make_shared<Model::Website>();
    createInstance(website);
    websitePersistence->addWebsite(website);
}

void Core::onRemoveInstance()
{
    Widget::Quietus *quietus = qobject_cast<Widget::Quietus *>(sender());
    quietus->deleteLater();
    const std::shared_ptr<Model::Website> website = quietus->getWebsite();
    websitePersistence->removeWebsite(website);
    if (websitePersistence->getWebsites().empty()) [[unlikely]]
    {
        onNewInstance();
    }
}
