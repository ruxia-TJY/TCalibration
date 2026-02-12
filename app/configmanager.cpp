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

        YAML::Node bordersize_node = yaml_config["Calibration"]["border_size"];

        if (!bordersize_node || !bordersize_node.IsSequence() || bordersize_node.size() != 2)
            throw std::runtime_error("border_size format error");

        m_bordersize.setWidth(bordersize_node[0].as<int>()) ;
        m_bordersize.setHeight(bordersize_node[1].as<int>());

    }
    catch (const YAML::Exception& e)
    {
        qCritical() << "YAML Error:" << e.what();
    }





    return true;
}

QSize ConfigManager::bordersize()
{
    return m_bordersize;
}