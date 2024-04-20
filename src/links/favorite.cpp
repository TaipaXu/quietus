#include "./favorite.hpp"
#include <algorithm>
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
        auto it = std::find_if(favoriteGroups.begin(), favoriteGroups.end(),
                               [&groupId](const auto &favoriteGroup) {
                                   return favoriteGroup->getId() == groupId;
                               });

        if (it != favoriteGroups.end())
        {
            (*it)->setName(name);
            Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
            favoritePersistence->saveFavoriteGroups(favoriteGroups);

            emit favoriteGroupsChanged();
        }
    }

    void Favorite::removeFavoriteGroup(const QString &groupId)
    {
        auto it = std::remove_if(favoriteGroups.begin(), favoriteGroups.end(),
                                 [&groupId](const auto &group) {
                                     return group->getId() == groupId;
                                 });

        if (it != favoriteGroups.end())
        {
            favoriteGroups.erase(it, favoriteGroups.end());
            Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
            favoritePersistence->saveFavoriteGroups(favoriteGroups);

            emit favoriteGroupsChanged();
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

        auto it = std::find_if(favoriteGroups.begin(), favoriteGroups.end(),
                               [&groupId](const auto &group) {
                                   return group->getId() == groupId;
                               });

        if (it != favoriteGroups.end())
        {
            Model::Website *favorite = new Model::Website(name, favicon, url, *it);
            (*it)->addWebsite(favorite);

            Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
            favoritePersistence->saveFavoriteGroups(favoriteGroups);

            emit favoriteGroupsChanged();
        }
    }

    void Favorite::editFavoriteWebsite(const QString &websiteId, const QString &groupId, const QString &name, const QString &favicon, const QString &url)
    {
        Model::Website *foundWebsite = nullptr;
        Model::FavoriteGroup *originalGroup = nullptr;
        Model::FavoriteGroup *newGroup = nullptr;

        for (auto &&favoriteGroup : favoriteGroups)
        {
            auto it = std::find_if(favoriteGroup->getWebsites().begin(), favoriteGroup->getWebsites().end(),
                                   [&websiteId](const auto &website) {
                                       return website->getId() == websiteId;
                                   });

            if (it != favoriteGroup->getWebsites().end())
            {
                foundWebsite = *it;
                originalGroup = favoriteGroup;
                break;
            }
        }

        if (foundWebsite && originalGroup)
        {
            foundWebsite->setName(name);
            foundWebsite->setFavicon(favicon);
            foundWebsite->setUrl(url);

            if (originalGroup->getId() != groupId)
            {
                auto it = std::find_if(favoriteGroups.begin(), favoriteGroups.end(),
                                       [&groupId](const auto &group) {
                                           return group->getId() == groupId;
                                       });
                if (it != favoriteGroups.end())
                {
                    newGroup = *it;
                }
            }
            else
            {
                newGroup = originalGroup;
            }

            if (newGroup && newGroup != originalGroup)
            {
                originalGroup->takeWebsite(foundWebsite);
                newGroup->addWebsite(foundWebsite);
            }

            Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
            favoritePersistence->saveFavoriteGroups(favoriteGroups);

            emit favoriteGroupsChanged();
        }
    }

    void Favorite::removeFavoriteWebsite(const QString &url)
    {
        for (auto &&favoriteGroup : favoriteGroups)
        {
            auto it = std::find_if(favoriteGroup->getWebsites().begin(), favoriteGroup->getWebsites().end(),
                                   [&url](const auto &website) {
                                       return website->getUrl() == url;
                                   });

            if (it != favoriteGroup->getWebsites().end())
            {
                favoriteGroup->removeWebsite(*it);
                Persistence::Favorite *favoritePersistence = Persistence::Favorite::getInstance();
                favoritePersistence->saveFavoriteGroups(favoriteGroups);
                emit favoriteGroupsChanged();
                return;
            }
        }
    }

    bool Favorite::isFavoriteWebsite(const QString &url) const
    {
        return std::any_of(favoriteGroups.begin(), favoriteGroups.end(),
                           [&url](const auto &group) {
                               return std::any_of(group->getWebsites().begin(), group->getWebsites().end(),
                                                  [&url](const auto &website) {
                                                      return website->getUrl() == url;
                                                  });
                           });
    }
} // namespace Link
