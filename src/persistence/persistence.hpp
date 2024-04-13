#pragma once

#include <QString>

class QSettings;

namespace Persistence
{
    class Persistence
    {
    public:
        Persistence();
        virtual ~Persistence() = default;

        static QString getSettingsDirPath();
        static QString getSettingsFilePath(const QString &fileName);
        static QString getDataDirPath();
        static QString getDataFilePath(const QString &fileName);
        static void checkDir(const QString &dirPath);
        static void checkFile(const QString &filePath, const QString &content = QStringLiteral(""));

    protected:
        virtual void readSettings() = 0;
        virtual void writeSettings() = 0;
    };
} // namespace Persistence
