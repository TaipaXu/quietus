#pragma once

#include <memory>
#include <QObject>
#include <QString>
#include <QList>
#include "models/website.hpp"

namespace Model
{
    class FavoriteGroup : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString id READ getId CONSTANT)
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QList<Model::Website *> websites READ getWebsites NOTIFY websitesChanged)

    public:
        FavoriteGroup(QObject *parent = nullptr);
        FavoriteGroup(const QString &id, const QString &name, const QList<Model::Website *> &websites, QObject *parent = nullptr);
        FavoriteGroup(const QString &name, const QList<Model::Website *> &websites = {}, QObject *parent = nullptr);
        ~FavoriteGroup() = default;

        const QString &getId() const;
        const QString &getName() const;
        void setName(const QString &name);
        const QList<Model::Website *> &getWebsites() const;
        void addWebsite(Model::Website *website);
        void removeWebsite(Model::Website *website);
        void takeWebsite(Model::Website *website);

    signals:
        void nameChanged();
        void websitesChanged();

    private:
        const QString id;
        QString name;
        QList<Model::Website *> websites;
    };

    inline const QString &FavoriteGroup::getId() const
    {
        return id;
    }

    inline const QString &FavoriteGroup::getName() const
    {
        return name;
    }

    inline const QList<Model::Website *> &FavoriteGroup::getWebsites() const
    {
        return websites;
    }
} // namespace Model
