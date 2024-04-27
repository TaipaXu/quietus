#pragma once

#include <memory>
#include <QObject>
#include <QString>

namespace Model
{
    struct SizeAndPosition
    {
        int width;
        int height;
        int x;
        int y;
    };

    class Website : public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QString id READ getId CONSTANT)
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString favicon READ getFavicon WRITE setFavicon NOTIFY faviconChanged)
        Q_PROPERTY(QString url READ getUrl WRITE setUrl NOTIFY urlChanged)
        Q_PROPERTY(bool mobileMode READ isMobileMode WRITE setMobileMode NOTIFY mobileModeChanged)

    public:
        Website(QObject *parent = nullptr);
        Website(const QString &id, const QString &name, const QString &favicon, const QString &url, bool mobileMode = true, std::unique_ptr<SizeAndPosition> &&sizeAndPosition = nullptr, QObject *parent = nullptr);
        Website(const QString &name, const QString &favicon, const QString &url, bool mobileMode = true, std::unique_ptr<SizeAndPosition> &&sizeAndPosition = nullptr, QObject *parent = nullptr);
        ~Website() = default;

        const QString &getId() const;
        const QString &getName() const;
        void setName(const QString &name);
        const QString &getFavicon() const;
        void setFavicon(const QString &favicon);
        const QString &getUrl() const;
        void setUrl(const QString &url);
        bool isMobileMode() const;
        void setMobileMode(bool mobileMode);
        bool hasSizeAndPosition() const;
        void setSizeAndPosition(int width, int height, int x, int y);
        int getWidth() const;
        int getHeight() const;
        int getX() const;
        int getY() const;
        void clear();

    signals:
        void nameChanged();
        void faviconChanged();
        void urlChanged();
        void mobileModeChanged();

    private:
        const QString id;
        QString name;
        QString favicon;
        QString url;
        bool mobileMode;
        std::unique_ptr<SizeAndPosition> sizeAndPosition;
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

    inline bool Website::isMobileMode() const
    {
        return mobileMode;
    }

    inline bool Website::hasSizeAndPosition() const
    {
        return sizeAndPosition != nullptr;
    }

    inline int Website::getWidth() const
    {
        return sizeAndPosition ? sizeAndPosition->width : 0;
    }

    inline int Website::getHeight() const
    {
        return sizeAndPosition ? sizeAndPosition->height : 0;
    }

    inline int Website::getX() const
    {
        return sizeAndPosition ? sizeAndPosition->x : 0;
    }

    inline int Website::getY() const
    {
        return sizeAndPosition ? sizeAndPosition->y : 0;
    }
} // namespace Model
