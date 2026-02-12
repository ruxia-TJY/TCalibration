#include "mainwindow.h"
#include <QApplication>
#include <QStandardPaths>
#include "configmanager.h"

int main(int argc, char *argv[])
{
#ifdef DEV_MODE
    qDebug() << "Dev mode";

    QString configPath =
        QStandardPaths::writableLocation(
            QStandardPaths::AppConfigLocation);

    QDir dir(configPath);

    if (!dir.exists()) {
        qDebug() << "Config directory does not exist";
        return false;
    }

    bool ok = dir.removeRecursively();

    if (ok)
        qDebug() << "Config directory removed:" << configPath;
    else
        qDebug() << "Failed to remove:" << configPath;


#endif
    QApplication a(argc, argv);
    a.setApplicationName("TCalibration");
    a.setApplicationDisplayName("TCalibration");
    a.setApplicationVersion("1.0.0");

    QString config_file_path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/config.ini";
    qDebug() << "Config File Path:" << config_file_path;

    if (!ConfigManager::instance().load(config_file_path)) {
        QMessageBox::critical(nullptr, "Error", "配置文件读取失败");
        return -1;
    }

    MainWindow w;

    w.show();
    return a.exec();
}
