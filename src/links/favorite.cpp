#include "./favorite.hpp"
#include "persistence/favorite.hpp"
#include "models/website.hpp"

namespace Link
{
    Favorite::Favorite(QObject *parent)
        : QObject(parent)
    {
        Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
        favoriteGroups = favoritePersistence->getFavoriteGroups();
    }

    Favorite *Favorite::getInstance()
    {
        static Favorite instance;
        return &instance;
    }

    Favorite::~Favorite()
    {
        for (auto &&favoriteGroup : favoriteGroups)
        {
            favoriteGroup->deleteLater();
        }
    }

    void Favorite::addFavoriteGroup(Model::FavoriteGroup *favoriteGroup)
    {
        favoriteGroups.append(favoriteGroup);

        emit favoriteGroupsChanged();
    }

    void Favorite::addFavoriteGroup(const QString &name)
    {
        Model::FavoriteGroup *favoriteGroup = new Model::FavoriteGroup(name);
        favoriteGroups.append(favoriteGroup);

        Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
        favoritePersistence->saveFavoriteGroups(favoriteGroups);

        emit favoriteGroupsChanged();
    }

    void Favorite::editFavoriteGroup(const QString &groupId, const QString &name)
    {
        for (auto &&favoriteGroup : favoriteGroups)
        {
            if (favoriteGroup->getId() == groupId)
            {
                favoriteGroup->setName(name);
                Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
                favoritePersistence->saveFavoriteGroups(favoriteGroups);

                emit favoriteGroupsChanged();

                return;
            }
        }
    }

    void Favorite::removeFavoriteGroup(const QString &groupId)
    {
        for (int i = 0; i < favoriteGroups.size(); i++)
        {
            if (favoriteGroups[i]->getId() == groupId)
            {
                favoriteGroups.removeAt(i);
                Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
                favoritePersistence->saveFavoriteGroups(favoriteGroups);

                emit favoriteGroupsChanged();

                return;
            }
        }
    }

    void Favorite::setFavoriteGroups(const QList<Model::FavoriteGroup *> &favoriteGroups)
    {
        this->favoriteGroups = favoriteGroups;
        emit favoriteGroupsChanged();
    }

    void Favorite::addFavoriteWebsite(const QString &groupId, const QString &name, const QString &favicon, const QString &url)
    {
        if (isFavoriteWebsite(url))
        {
            return;
        }

        Model::FavoriteGroup *group = nullptr;
        for (auto &&favoriteGroup : favoriteGroups)
        {
            if (favoriteGroup->getId() == groupId)
            {
                group = favoriteGroup;
                break;
            }
        }

        if (group != nullptr)
        {
            Model::Website *favorite = new Model::Website(name, favicon, url, group);
            group->addWebsite(favorite);

            Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
            favoritePersistence->saveFavoriteGroups(favoriteGroups);
        }

        emit favoriteGroupsChanged();
    }

    void Favorite::editFavoriteWebsite(const QString &websiteId, const QString &groupId, const QString &name, const QString &favicon, const QString &url)
    {
        for (auto &&favoriteGroup : favoriteGroups)
        {

            for (auto &&favorite : favoriteGroup->getWebsites())
            {
                if (favorite->getId() == websiteId)
                {
                    favorite->setName(name);
                    favorite->setFavicon(favicon);
                    favorite->setUrl(url);

                    favoriteGroup->takeWebsite(favorite);
                    for (auto &&group : favoriteGroups)
                    {
                        if (group->getId() == groupId)
                        {
                            group->addWebsite(favorite);

                            Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
                            favoritePersistence->saveFavoriteGroups(favoriteGroups);

                            emit favoriteGroupsChanged();

                            return;
                        }
                    }
                    break;
                }
            }
        }
    }

    void Favorite::removeFavoriteWebsite(const QString &url)
    {
        for (auto &&favoriteGroup : favoriteGroups)
        {
            for (auto &&favorite : favoriteGroup->getWebsites())
            {
                if (favorite->getUrl() == url)
                {
                    favoriteGroup->removeWebsite(favorite);
                    Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
                    favoritePersistence->saveFavoriteGroups(favoriteGroups);
                    return;
                }
            }
        }

        emit favoriteGroupsChanged();
    }

    bool Favorite::isFavoriteWebsite(const QString &url) const
    {
        for (auto &&favoriteGroup : favoriteGroups)
        {
            for (auto &&favorite : favoriteGroup->getWebsites())
            {
                if (favorite->getUrl() == url)
                {
                    return true;
                }
            }
        }

        return false;
    }
} // namespace Link
