#include "./website.hpp"
#include "utils/common.hpp"

namespace Model
{
    Website::Website(const QString &id, const QString &name, const QString &favicon, const QString &url)
        : id{id}, name(name), favicon(favicon), url(url)
    {
    }

    Website::Website(const QString &name, const QString &favicon, const QString &url)
        : Website(Util::Common::getUuid(), name, favicon, url)
    {
    }

    Website::Website()
        : Website("", "", "")
    {
    }

    Website::~Website()
    {
    }

    void Website::setName(const QString &name)
    {
        if (this->name != name)
        {
            this->name = name;
        }
    }

    void Website::setFavicon(const QString &favicon)
    {
        if (this->favicon != favicon)
        {
            this->favicon = favicon;
        }
    }

    void Website::setUrl(const QString &url)
    {
        if (this->url != url)
        {
            this->url = url;
        }
    }

    void Website::clear()
    {
        name.clear();
        favicon.clear();
        url.clear();
    }
} // namespace Model
