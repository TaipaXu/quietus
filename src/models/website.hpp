#pragma once

#include <QString>

namespace Model
{
    class Website
    {
    public:
        Website(const QString &id, const QString &name, const QString &favicon, const QString &url, bool mobileMode = true);
        Website(const QString &name, const QString &favicon, const QString &url, bool mobileMode = true);
        Website();
        ~Website();

        const QString &getId() const;
        const QString &getName() const;
        void setName(const QString &name);
        const QString &getFavicon() const;
        void setFavicon(const QString &favicon);
        const QString &getUrl() const;
        void setUrl(const QString &url);
        bool isMobileMode() const;
        void setMobileMode(bool mobileMode);
        void clear();

    private:
        const QString id;
        QString name;
        QString favicon;
        QString url;
        bool mobileMode;
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
} // namespace Model
