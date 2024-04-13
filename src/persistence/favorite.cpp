#include "./favorite.hpp"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

namespace Persistence
{
    Favorite::Favorite()
    {
        checkDataFile();
        readSettings();
    }

    Favorite *Favorite::getInstance()
    {
        static Favorite instance;
        return &instance;
    }

    Favorite::~Favorite()
    {
    }

    QList<Model::FavoriteGroup *> Favorite::getFavoriteGroups() const
    {
        QFile file(getDataFilePath());
        if (!file.open(QIODevice::ReadOnly))
        {
            return QList<Model::FavoriteGroup *>();
        }

        const QByteArray data = file.readAll();
        QJsonParseError error;
        const QJsonDocument doc = QJsonDocument::fromJson(data, &error);
        if (error.error != QJsonParseError::NoError)
        {
            return QList<Model::FavoriteGroup *>();
        }

        QList<Model::FavoriteGroup *> favoriteGroups;
        const QJsonObject root = doc.object();
        const QJsonArray favoritesArray = root["favorites"].toArray();
        for (auto &&favoriteJson : favoritesArray)
        {
            const QJsonObject favoriteObject = favoriteJson.toObject();
            const QString id = favoriteObject["id"].toString();
            const QString name = favoriteObject["name"].toString();

            const QJsonArray websitesArray = favoriteObject["websites"].toArray();
            QList<Model::Website *> websites;
            for (auto &&websiteJson : websitesArray)
            {
                const QJsonObject websiteObject = websiteJson.toObject();
                const QString id = websiteObject["id"].toString();
                const QString websiteName = websiteObject["name"].toString();
                const QString favicon = websiteObject["favicon"].toString();
                const QString url = websiteObject["url"].toString();
                const bool isMobileMode = websiteObject["isMobileMode"].toBool(true);

                Model::Website *websiteModel = new Model::Website(id, websiteName, favicon, url, isMobileMode);
                websites.push_back(websiteModel);
            }
            Model::FavoriteGroup *favoriteGroup = new Model::FavoriteGroup(id, name, websites);
            favoriteGroups.push_back(favoriteGroup);
        }
        return favoriteGroups;
    }

    void Favorite::saveFavoriteGroups(const QList<Model::FavoriteGroup *> &favoriteGroups)
    {
        QFile file(getDataFilePath());
        if (!file.open(QIODevice::WriteOnly))
        {
            return;
        }

        QJsonObject root;
        QJsonArray favoritesArray;
        for (const auto &favoriteGroup : favoriteGroups)
        {
            QJsonObject favoriteObject;
            favoriteObject["id"] = favoriteGroup->getId();
            favoriteObject["name"] = favoriteGroup->getName();

            QJsonArray websitesArray;
            for (const auto &website : favoriteGroup->getWebsites())
            {
                QJsonObject websiteObject;
                websiteObject["id"] = website->getId();
                websiteObject["name"] = website->getName();
                websiteObject["favicon"] = website->getFavicon();
                websiteObject["url"] = website->getUrl();
                websiteObject["isMobileMode"] = website->isMobileMode();

                websitesArray.append(websiteObject);
            }
            favoriteObject["websites"] = websitesArray;
            favoritesArray.append(favoriteObject);
        }
        root["favorites"] = favoritesArray;

        QJsonDocument doc(root);
        file.write(doc.toJson());
    }

    void Favorite::readSettings()
    {
        QFile file(getDataFilePath());
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }

        const QByteArray data = file.readAll();
        QJsonParseError error;
        const QJsonDocument doc = QJsonDocument::fromJson(data, &error);
        if (error.error != QJsonParseError::NoError)
        {
            return;
        }

        QList<Model::FavoriteGroup *> favoriteGroups;
        const QJsonObject root = doc.object();
        const QJsonArray favoritesArray = root["favorites"].toArray();
        for (auto &&favoriteJson : favoritesArray)
        {
            const QJsonObject favoriteObject = favoriteJson.toObject();
            const QString id = favoriteObject["id"].toString();
            const QString name = favoriteObject["name"].toString();

            const QJsonArray websitesArray = favoriteObject["websites"].toArray();
            QList<Model::Website *> websites;
            for (auto &&websiteJson : websitesArray)
            {
                const QJsonObject websiteObject = websiteJson.toObject();
                const QString id = websiteObject["id"].toString();
                const QString websiteName = websiteObject["name"].toString();
                const QString favicon = websiteObject["favicon"].toString();
                const QString url = websiteObject["url"].toString();
                const bool isMobileMode = websiteObject["isMobileMode"].toBool(true);

                Model::Website *websiteModel = new Model::Website(id, websiteName, favicon, url, isMobileMode);
                websites.push_back(websiteModel);
            }
            Model::FavoriteGroup *favoriteGroup = new Model::FavoriteGroup(id, name, websites);
            favoriteGroups.push_back(favoriteGroup);
        }
    }

    void Favorite::writeSettings()
    {
        // QFile file(getDataFilePath());
        // if (!file.open(QIODevice::WriteOnly))
        // {
        //     return;
        // }

        // QJsonObject root;
        // QJsonArray favoritesArray;
        // for (const auto &favoriteGroup : favoriteGroups)
        // {
        //     QJsonObject favoriteObject;
        //     favoriteObject["id"] = favoriteGroup->getId();
        //     favoriteObject["name"] = favoriteGroup->getName();

        //     QJsonArray websitesArray;
        //     for (const auto &website : favoriteGroup->getWebsites())
        //     {
        //         QJsonObject websiteObject;
        //         websiteObject["id"] = website->getId();
        //         websiteObject["name"] = website->getName();
        //         websiteObject["favicon"] = website->getFavicon();
        //         websiteObject["url"] = website->getUrl();
        //         websiteObject["isMobileMode"] = website->isMobileMode();

        //         websitesArray.append(websiteObject);
        //     }
        //     favoriteObject["websites"] = websitesArray;
        //     favoritesArray.append(favoriteObject);
        // }
        // root["favorites"] = favoritesArray;

        // QJsonDocument doc(root);
        // file.write(doc.toJson());
    }

    QString Favorite::getDataFilePath() const
    {
        return Persistence::getDataFilePath(QStringLiteral("favorites.json"));
    }

    void Favorite::checkDataFile() const
    {
        const QString dirPath = Persistence::getDataDirPath();
        const QString filePath = getDataFilePath();
        Persistence::checkDir(dirPath);
        Persistence::checkFile(filePath, "{}");
    }
} // namespace Persistence
