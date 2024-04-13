#include "./website.hpp"
#include "utils/common.hpp"

namespace Model
{
    Website::Website(const QString &id, const QString &name, const QString &favicon, const QString &url, bool mobileMode)
        : id{id}, name(name), favicon(favicon), url(url), mobileMode(mobileMode)
    {
    }

    Website::Website(const QString &name, const QString &favicon, const QString &url, bool mobileMode)
        : Website(Util::Common::getUuid(), name, favicon, url, mobileMode)
    {
    }

    Website::Website()
        : Website("", "", "", true)
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

    void Website::setMobileMode(bool mobileMode)
    {
        if (this->mobileMode != mobileMode)
        {
            this->mobileMode = mobileMode;
        }
    }

    void Website::clear()
    {
        name.clear();
        favicon.clear();
        url.clear();
    }
} // namespace Model
