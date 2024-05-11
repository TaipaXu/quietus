#pragma once

#include <QObject>
#include <QString>
#include "models/website.hpp"

namespace Model
{
    struct SizeAndPosition
    {
        int width;
        int height;
        int x;
        int y;
    };

    class BrowserWebsite : public Website
    {
        Q_OBJECT

        Q_PROPERTY(bool mobileMode READ isMobileMode WRITE setMobileMode NOTIFY mobileModeChanged)

    public:
        BrowserWebsite(QObject *parent = nullptr);
        BrowserWebsite(const QString &id, const QString &name, const QString &favicon, const QString &url, bool mobileMode = true, std::unique_ptr<SizeAndPosition> &&sizeAndPosition = nullptr, QObject *parent = nullptr);
        BrowserWebsite(const QString &name, const QString &favicon, const QString &url, bool mobileMode = true, std::unique_ptr<SizeAndPosition> &&sizeAndPosition = nullptr, QObject *parent = nullptr);
        ~BrowserWebsite() = default;

        bool isMobileMode() const;
        void setMobileMode(bool mobileMode);
        bool hasSizeAndPosition() const;
        void setSizeAndPosition(int width, int height, int x, int y);
        void clearSizeAndPosition();
        int getWidth() const;
        int getHeight() const;
        int getX() const;
        int getY() const;
        void clear();

    signals:
        void mobileModeChanged();

    private:
        bool mobileMode;
        std::unique_ptr<SizeAndPosition> sizeAndPosition;
    };

    inline bool BrowserWebsite::isMobileMode() const
    {
        return mobileMode;
    }

    inline bool BrowserWebsite::hasSizeAndPosition() const
    {
        return sizeAndPosition != nullptr;
    }

    inline int BrowserWebsite::getWidth() const
    {
        return sizeAndPosition ? sizeAndPosition->width : 0;
    }

    inline int BrowserWebsite::getHeight() const
    {
        return sizeAndPosition ? sizeAndPosition->height : 0;
    }

    inline int BrowserWebsite::getX() const
    {
        return sizeAndPosition ? sizeAndPosition->x : 0;
    }

    inline int BrowserWebsite::getY() const
    {
        return sizeAndPosition ? sizeAndPosition->y : 0;
    }
} // namespace Model
