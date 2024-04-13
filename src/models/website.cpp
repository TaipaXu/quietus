#include "./website.hpp"
#include "utils/common.hpp"

namespace Model
{
    Website::Website(QObject *parent)
        : QObject(parent), mobileMode(false)
    {
    }

    Website::Website(const QString &id, const QString &name, const QString &favicon, const QString &url, bool mobileMode, QObject *parent)
        : QObject(parent), id{id}, name(name), favicon(favicon), url(url), mobileMode(mobileMode)
    {
    }

    Website::Website(const QString &name, const QString &favicon, const QString &url, bool mobileMode, QObject *parent)
        : Website(Util::Common::getUuid(), name, favicon, url, mobileMode, parent)
    {
    }

    void Website::setName(const QString &name)
    {
        if (this->name != name)
        {
            this->name = name;

            emit nameChanged();
        }
    }

    void Website::setFavicon(const QString &favicon)
    {
        if (this->favicon != favicon)
        {
            this->favicon = favicon;

            emit faviconChanged();
        }
    }

    void Website::setUrl(const QString &url)
    {
        if (this->url != url)
        {
            this->url = url;

            emit urlChanged();
        }
    }

    void Website::setMobileMode(bool mobileMode)
    {
        if (this->mobileMode != mobileMode)
        {
            this->mobileMode = mobileMode;

            emit mobileModeChanged();
        }
    }

    void Website::clear()
    {
        name.clear();
        favicon.clear();
        url.clear();

        emit nameChanged();
        emit faviconChanged();
        emit urlChanged();
    }
} // namespace Model
