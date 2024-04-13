#include "./website.hpp"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

namespace Persistence
{
    Website::Website()
    {
        checkDataFile();
        readSettings();
    }

    Website *Website::getInstance()
    {
        static Website instance;
        return &instance;
    }

    Website::~Website()
    {
        websites.clear();
    }

    const std::list<std::shared_ptr<Model::Website>> &Website::getWebsites() const
    {
        return websites;
    }

    void Website::addWebsite(const std::shared_ptr<Model::Website> &website)
    {
        websites.push_back(website);
        writeSettings();
    }

    void Website::removeWebsite(const std::shared_ptr<Model::Website> &website)
    {
        websites.remove(website);
        writeSettings();
    }

    void Website::updateWebsites()
    {
        writeSettings();
    }

    void Website::readSettings()
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

        const QJsonObject root = doc.object();
        const QJsonArray websitesArray = root["websites"].toArray();
        for (auto &&websiteJson : websitesArray)
        {
            const QJsonObject websiteObject = websiteJson.toObject();
            const QString id = websiteObject["id"].toString();
            const QString name = websiteObject["name"].toString();
            const QString favicon = websiteObject["favicon"].toString();
            const QString url = websiteObject["url"].toString();

            const std::shared_ptr<Model::Website> websiteModel = std::make_shared<Model::Website>(name, favicon, url);
            websites.push_back(websiteModel);
        }
    }

    void Website::writeSettings()
    {
        QFile file(getDataFilePath());
        if (!file.open(QIODevice::WriteOnly))
        {
            return;
        }

        QJsonObject root;
        QJsonArray websitesArray;
        for (const auto &website : websites)
        {
            QJsonObject websiteObject;
            websiteObject["id"] = website->getId();
            websiteObject["name"] = website->getName();
            websiteObject["favicon"] = website->getFavicon();
            websiteObject["url"] = website->getUrl();

            websitesArray.append(websiteObject);
        }
        root["websites"] = websitesArray;

        const QJsonDocument doc(root);
        file.write(doc.toJson());
    }

    QString Website::getDataFilePath() const
    {
        return Persistence::getDataFilePath(QStringLiteral("websites.json"));
    }

    void Website::checkDataFile() const
    {
        const QString dirPath = Persistence::getDataDirPath();
        const QString filePath = getDataFilePath();
        Persistence::checkDir(dirPath);
        Persistence::checkFile(filePath, "{}");
    }
} // namespace Persistence
