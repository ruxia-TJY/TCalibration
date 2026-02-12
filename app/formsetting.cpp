#include "formsetting.h"
#include "ui_formsetting.h"

FormSetting::FormSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSetting)
{
    ui->setupUi(this);

    connect(ui->pBSave,&QPushButton::clicked,this,&FormSetting::onPbSaveClicked);
    connect(ui->pBCancel,&QPushButton::clicked,this,&FormSetting::onPbCancelClicked);

    LoadConfig();
}

FormSetting::~FormSetting()
{
    delete ui;
}


void FormSetting::LoadConfig()
{
    ui->sBWidth->setValue(ConfigManager::instance().bordersize().width());
    ui->sBHeight->setValue(ConfigManager::instance().bordersize().height());

}


void FormSetting::onPbSaveClicked()
{
    qDebug() << "clickle";
}

void FormSetting::onPbCancelClicked()
{

}