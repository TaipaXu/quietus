#pragma once

#include <QObject>
#include <QString>

namespace Util
{
    class Common : public QObject
    {
        Q_OBJECT

    public:
        Common(QObject *parent = nullptr);
        ~Common() = default;

        static QString getUuid();
        Q_INVOKABLE bool isValidUrl(const QString &url);
    };
} // namespace Util
