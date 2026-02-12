#include "mainwindow.h"

#include "debug_log.h"
#include "ui_mainwindow.h"
#include  "opencv2/opencv.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lWList->setEditTriggers(
        QAbstractItemView::DoubleClicked |
        QAbstractItemView::EditKeyPressed);

    ui->lblPlayer->setAlignment(Qt::AlignCenter);
    ui->lblPlayer->setStyleSheet("border 1px");

    connect(ui->pbLoad,&QPushButton::clicked,this,&MainWindow::onPbLoadClicked);
    connect(ui->pbRename,&QPushButton::clicked,this,&MainWindow::onPbRenameClicked);
    connect(ui->lWList, &QListWidget::itemDoubleClicked,
        this, &MainWindow::onItemDoubleClicked);
    connect(ui->lWList, &QListWidget::itemChanged,
            this, &MainWindow::onItemNameChanged);
    connect(ui->lWList,&QListWidget::currentItemChanged,this,&MainWindow::onCurrentItemChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPbCalcClicked()
{
    
}

void MainWindow::onCurrentItemChanged(QListWidgetItem *current,
                                      QListWidgetItem *previous)
{
    Q_UNUSED(previous);
    if (current == nullptr)return;

    QString imgPath = current->data(Qt::UserRole).toString();
    show_image(imgPath);
}

void MainWindow::show_image(QString imagePath)
{
    QPixmap pixmap;
    if (!pixmap.load(imagePath))
    {
        ui->lblPlayer->setText("Failed to load");
        return;
    }

    QPixmap scaled = pixmap.scaled(
        ui->lblPlayer->size(),
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->lblPlayer->setPixmap(scaled);
}

void MainWindow::show_image(int img_index_in_lw)
{
    if (img_index_in_lw > ui->lWList->count())return;

    QString img_path = ui->lWList->currentItem()->data(Qt::UserRole).toString();
    show_image(img_path);
}

void MainWindow::onPbRenameClicked()
{
    if (this->FolderPath.isEmpty())return;

    const QString prefix = "Img_";
    const int startIndex = 1;
    const int padWidth = 3;   // 001
    const QString forceSuffix = "bmp"; // 若不想强制，设为空 ""

    struct RenamePair {
        QString oldPath;
        QString newPath;
    };

    QVector<RenamePair> renameList;

    // 1️⃣ 生成目标文件名（不立即重命名）
    for (int i = 0; i < ui->lWList->count(); ++i)
    {
        QListWidgetItem *item = ui->lWList->item(i);
        QFileInfo oldInfo(item->data(Qt::UserRole).toString());

        QString suffix = forceSuffix.isEmpty()
                             ? oldInfo.suffix()
                             : forceSuffix;

        QString newName = QString("%1%2.%3")
                              .arg(prefix)
                              .arg(startIndex + i, padWidth, 10, QChar('0'))
                              .arg(suffix);

        QString newPath = oldInfo.dir().absoluteFilePath(newName);

        renameList.push_back({ oldInfo.absoluteFilePath(), newPath });
    }

    // 2️⃣ 第一阶段：改成临时名，避免冲突
    for (int i = 0; i < renameList.size(); ++i)
    {
        QString tempPath = renameList[i].oldPath + ".tmp_rename";
        QFile::rename(renameList[i].oldPath, tempPath);
        renameList[i].oldPath = tempPath;
    }

    // 3️⃣ 第二阶段：改成最终名
    for (int i = 0; i < renameList.size(); ++i)
    {
        if (!QFile::rename(renameList[i].oldPath, renameList[i].newPath))
        {
            qCritical() << "Rename failed:" << renameList[i].oldPath;
            return;
        }
    }

    load_image(this->FolderPath);
}

void MainWindow::onItemNameChanged(QListWidgetItem *item)
{
    QString oldPath = item->data(Qt::UserRole).toString();
    QFileInfo oldInfo(oldPath);

    QString baseName = item->text().trimmed();
    //
    if (baseName.isEmpty())
    {
        ui->lWList->blockSignals(true);
        item->setText(baseName);
        ui->lWList->blockSignals(false);
        item->setText(oldInfo.fileName());
        return;
    }

    if (!baseName.contains("."))
    {
        baseName += "." + oldInfo.suffix();
        ui->lWList->blockSignals(true);
        item->setText(baseName);
        ui->lWList->blockSignals(false);
    }

    QString newPath = oldInfo.dir().absoluteFilePath(baseName);

    if (oldPath == newPath)return;

    if (QFile::exists(newPath))
    {
        QMessageBox::warning(this,"提示","文件已经存在！");
        item->setText(oldInfo.fileName());
        return;
    }

    if (!QFile::rename(oldPath, newPath))
    {
        QMessageBox::critical(this,"警告","文件重命名失败");
        item->setText(oldInfo.fileName());
        return;
    }

    item->setData(Qt::UserRole,newPath);

    qDebug() << "Renamed:" << oldPath << "->" << newPath;
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item)
{
    if (item == nullptr)return;
    ui->lWList->editItem(item);
}

void MainWindow::load_image(QString folderPath)
{
    ui->lWList->clear();

    QDir dir(folderPath);
    QStringList filters;
    filters << "*.jpg" << "*.bmp" << "*.jpg";

    QFileInfoList fileInfoList = dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot);

    for (const QFileInfo &fileInfo : fileInfoList)
    {
        QListWidgetItem *item = new QListWidgetItem(fileInfo.fileName());

        item->setData(Qt::UserRole, fileInfo.absoluteFilePath());
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        ui->lWList->addItem(item);
    }

    if (ui->lWList->count() > 0)
        ui->lWList->setCurrentRow(0);
}

void MainWindow::onPbLoadClicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this,
        "选择图片路径","",QFileDialog::ShowDirsOnly);

    if (folderPath.isEmpty())return;

    load_image(folderPath);
    ui->statusbar->showMessage(folderPath);
    this->FolderPath = folderPath;
}
