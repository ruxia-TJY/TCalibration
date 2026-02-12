#include "mainwindow.h"
#include <QApplication>
#include <QStandardPaths>
#include "configmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
