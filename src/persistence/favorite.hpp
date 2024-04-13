#pragma once

#include "./persistence.hpp"
#include <list>
#include <memory>
#include "models/favorite.hpp"

namespace Persistence
{
    class Favorite : public Persistence
    {
    public:
        Favorite();
        static Favorite *getInstance();
        ~Favorite();

        QList<Model::FavoriteGroup *> getFavoriteGroups() const;
        void saveFavoriteGroups(const QList<Model::FavoriteGroup *> &favoriteGroups);

    private:
        void readSettings() override;
        void writeSettings() override;

        QString getDataFilePath() const;
        void checkDataFile() const;
    };
} // namespace Persistence
