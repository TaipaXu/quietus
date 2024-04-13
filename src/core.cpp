#include "./core.hpp"
#include <QQmlEngine>
#include "widgets/quietus.hpp"
#include "persistence/website.hpp"
#include "models/website.hpp"
#include "utils/common.hpp"

Core::Core()
{
    qmlRegisterType<Util::Common>("utils", 1, 0, "Utils");

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