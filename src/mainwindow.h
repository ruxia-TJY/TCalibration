#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>

#include  "debug_log.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void load_image(QString folderPath);
    void onPbLoadClicked();
    void onPbRenameClicked();
    void onPbCalcClicked();
    void show_image(QString imagePath);
    void show_image(int img_index_in_lw);
    void onCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void onItemDoubleClicked(QListWidgetItem *item);
    void onItemNameChanged(QListWidgetItem *item);
private:
    Ui::MainWindow *ui;

    QString FolderPath;
};
#endif // MAINWINDOW_H
