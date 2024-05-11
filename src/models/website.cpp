#include "./website.hpp"
#include "utils/common.hpp"

namespace Model
{
    Website::Website(QObject *parent)
        : QObject(parent)
    {
    }

    Website::Website(const QString &id, const QString &name, const QString &favicon, const QString &url, QObject *parent)
        : QObject(parent), id{id}, name{name}, favicon{favicon}, url{url}
    {
    }

    Website::Website(const QString &name, const QString &favicon, const QString &url, QObject *parent)
        : Website(Util::Common::getUuid(), name, favicon, url, parent)
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
} // namespace Model
