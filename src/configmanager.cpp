//
// Created by jared on 2026/2/7.
//

#include "configmanager.h"


ConfigManager& ConfigManager::instance()
{
    static ConfigManager instance;
    return instance;
}

bool ConfigManager::load(const QString& path)
{
    if (!QFileInfo::exists(path))
    {
        if (!QDir().mkpath(QFileInfo(path).dir().absolutePath()))
        {
            qCritical() << "Failed to create directory" << QFileInfo(path).absolutePath();
            return false;
        }

        QFile src(":/config/resources/config.yaml");
        if (!src.exists())
        {
            qCritical() << "Default config not found in resources";
            return false;
        }

        if (!src.copy(path))
        {
            qCritical() << "Failed to copy" << QFileInfo(path).absolutePath();
            return false;
        }

        QFile::setPermissions(path,QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    }

    qDebug() << "Successfully loaded" << QFileInfo(path).absolutePath();

    try
    {
        yaml_config = YAML::LoadFile(path.toStdString());
    }
    catch (const YAML::Exception& e)
    {
        qCritical() << "YAML Error:" << e.what();
    }





    return true;
}