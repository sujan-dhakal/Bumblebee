#include "current.h"
#include "ui_current.h"

Current::Current(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Current)
{
    ui->setupUi(this);
}

Current::~Current()
{
    delete ui;
}
