#include "./favorite.hpp"
#include "utils/common.hpp"

namespace Model
{
    FavoriteGroup::FavoriteGroup(QObject *parent)
        : QObject(parent)
    {
    }

    FavoriteGroup::FavoriteGroup(const QString &id, const QString &name, const QList<Model::Website *> &websites, QObject *parent)
        : QObject(parent), id{id}, name{name}, websites{websites}
    {
    }

    FavoriteGroup::FavoriteGroup(const QString &name, const QList<Model::Website *> &websites, QObject *parent)
        : FavoriteGroup(Util::Common::getUuid(), name, websites, parent)
    {
    }

    void FavoriteGroup::setName(const QString &name)
    {
        if (this->name != name)
        {
            this->name = name;

            emit nameChanged();
        }
    }

    void FavoriteGroup::addWebsite(Model::Website *website)
    {
        website->setParent(this);
        websites.append(website);

        emit websitesChanged();
    }

    void FavoriteGroup::removeWebsite(Model::Website *website)
    {
        website->setParent(nullptr);
        website->deleteLater();
        websites.removeOne(website);

        emit websitesChanged();
    }

    void FavoriteGroup::takeWebsite(Model::Website *website)
    {
        website->setParent(this);
        websites.removeOne(website);

        emit websitesChanged();
    }
} // namespace Model
