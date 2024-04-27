#pragma once

#include <QObject>
#include <QList>
#include "models/favorite.hpp"

namespace Link
{
    class Favorite : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QList<Model::FavoriteGroup *> favoriteGroups READ getFavoriteGroups WRITE setFavoriteGroups NOTIFY favoriteGroupsChanged)
        Q_PROPERTY(int favoriteGroupsCount READ getFavoriteGroupsCount NOTIFY favoriteGroupsChanged)

    public:
        Favorite(const Favorite &) = delete;
        Favorite &operator=(const Favorite &) = delete;
        static Favorite *getInstance();
        ~Favorite();

        QList<Model::FavoriteGroup *> getFavoriteGroups() const;
        void setFavoriteGroups(const QList<Model::FavoriteGroup *> &favoriteGroups);
        void addFavoriteGroup(Model::FavoriteGroup *favoriteGroup);
        Q_INVOKABLE void addFavoriteGroup(const QString &name);
        Q_INVOKABLE void editFavoriteGroup(const QString &groupId, const QString &name);
        Q_INVOKABLE void removeFavoriteGroup(const QString &groupId);
        int getFavoriteGroupsCount() const;
        Q_INVOKABLE void addFavoriteWebsite(const QString &groupId, const QString &name, const QString &favicon, const QString &url);
        Q_INVOKABLE void editFavoriteWebsite(const QString &websiteId, const QString &groupId, const QString &name, const QString &favicon, const QString &url);
        Q_INVOKABLE void removeFavoriteWebsite(const QString &url);
        Q_INVOKABLE bool isFavoriteWebsite(const QString &url) const;

    signals:
        void favoriteGroupsChanged();

    private:
        explicit Favorite(QObject *parent = nullptr);

    private:
        QList<Model::FavoriteGroup *> favoriteGroups;
    };

    inline QList<Model::FavoriteGroup *> Favorite::getFavoriteGroups() const
    {
        return favoriteGroups;
    }

    inline int Favorite::getFavoriteGroupsCount() const
    {
        return favoriteGroups.size();
    }
} // namespace Link
