//
// Created by jared on 2026/2/7.
//

#ifndef BD_CONFIGMANAGER_H
#define BD_CONFIGMANAGER_H

#include <QDir>
#include <yaml-cpp/yaml.h>

class ConfigManager
{
public:
    static ConfigManager& instance();

    QSize bordersize();

    bool load(const QString& path);
    void save(const QString& path);

    YAML::Node yaml_config;
private:
    QSize m_bordersize();

    ConfigManager() = default;
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
};


#endif //BD_CONFIGMANAGER_H