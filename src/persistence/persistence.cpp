#include "./persistence.hpp"
#include <QStandardPaths>
#include <QDir>

namespace Persistence
{
    Persistence::Persistence()
    {
    }

    QString Persistence::getSettingsDirPath()
    {
        return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    }

    QString Persistence::getSettingsFilePath(const QString &fileName)
    {
        return QString("%1/%2").arg(getSettingsDirPath()).arg(fileName);
    }

    QString Persistence::getDataDirPath()
    {
        return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }

    QString Persistence::getDataFilePath(const QString &fileName)
    {
        return QString("%1/%2").arg(getDataDirPath()).arg(fileName);
    }

    void Persistence::checkDir(const QString &dirPath)
    {
        QDir dir;
        if (!dir.exists(dirPath))
        {
            dir.mkpath(dirPath);
        }
    }

    void Persistence::checkFile(const QString &filePath, const QString &content)
    {
        QFile file(filePath);
        if (!file.exists())
        {
            if (file.open(QIODevice::WriteOnly))
            {
                file.write(content.toUtf8());
                file.close();
            }
        }
    }
} // namespace Persistence
