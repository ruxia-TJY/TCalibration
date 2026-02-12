#ifndef FORMSETTING_H
#define FORMSETTING_H

#include <QWidget>
#include "configmanager.h"

namespace Ui {
class FormSetting;
}

class FormSetting : public QWidget
{
    Q_OBJECT

public:
    explicit FormSetting(QWidget *parent = nullptr);
    ~FormSetting();

    void LoadConfig();

    void onPbSaveClicked();
    void onPbCancelClicked();
private:
    Ui::FormSetting *ui;

};

#endif // FORMSETTING_H
