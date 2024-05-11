#pragma once

#include <memory>
#include <QObject>
#include <QString>

namespace Model
{
    class Website : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString id READ getId CONSTANT)
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString favicon READ getFavicon WRITE setFavicon NOTIFY faviconChanged)
        Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)

    public:
        Website(QObject *parent = nullptr);
        Website(const QString &id, const QString &name, const QString &favicon, const QString &url, QObject *parent = nullptr);
        Website(const QString &name, const QString &favicon, const QString &url, QObject *parent = nullptr);
        ~Website() = default;

        const QString &getId() const;
        const QString &getName() const;
        void setName(const QString &name);
        const QString &getFavicon() const;
        void setFavicon(const QString &favicon);
        const QString &getUrl() const;
        void setUrl(const QString &url);

    signals:
        void nameChanged();
        void faviconChanged();
        void urlChanged();

    protected:
        const QString id;
        QString name;
        QString favicon;
        QString url;
    };

    inline const QString &Website::getId() const
    {
        return id;
    }

    inline const QString &Website::getName() const
    {
        return name;
    }

    inline const QString &Website::getFavicon() const
    {
        return favicon;
    }

    inline const QString &Website::getUrl() const
    {
        return url;
    }
} // namespace Model
