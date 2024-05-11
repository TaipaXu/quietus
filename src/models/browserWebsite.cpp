#include "./browserWebsite.hpp"

namespace Model
{
    BrowserWebsite::BrowserWebsite(QObject *parent)
        : Website(parent), mobileMode(true)
    {
    }

    BrowserWebsite::BrowserWebsite(const QString &id, const QString &name, const QString &favicon, const QString &url, bool mobileMode, std::unique_ptr<SizeAndPosition> &&sizeAndPosition, QObject *parent)
        : Website(id, name, favicon, url, parent), mobileMode{mobileMode}, sizeAndPosition{std::move(sizeAndPosition)}
    {
    }

    BrowserWebsite::BrowserWebsite(const QString &name, const QString &favicon, const QString &url, bool mobileMode, std::unique_ptr<SizeAndPosition> &&sizeAndPosition, QObject *parent)
        : Website(name, favicon, url, parent), mobileMode{mobileMode}, sizeAndPosition{std::move(sizeAndPosition)}
    {
    }

    void BrowserWebsite::setMobileMode(bool mobileMode)
    {
        if (this->mobileMode != mobileMode)
        {
            this->mobileMode = mobileMode;

            emit mobileModeChanged();
        }
    }

    void BrowserWebsite::setSizeAndPosition(int width, int height, int x, int y)
    {
        if (sizeAndPosition)
        {
            sizeAndPosition->width = width;
            sizeAndPosition->height = height;
            sizeAndPosition->x = x;
            sizeAndPosition->y = y;
        }
        else
        {
            sizeAndPosition = std::move(std::make_unique<SizeAndPosition>(width, height, x, y));
        }
    }

    void BrowserWebsite::clearSizeAndPosition()
    {
        sizeAndPosition.reset();
    }

    void BrowserWebsite::clear()
    {
        name.clear();
        favicon.clear();
        url.clear();

        emit nameChanged();
        emit faviconChanged();
        emit urlChanged();
    }
} // namespace Model
