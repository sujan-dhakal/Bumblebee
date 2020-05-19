#include "historymainwidget.h"
#include "ui_historymainwidget.h"

HistoryMainWidget::HistoryMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryMainWidget)
{
    ui->setupUi(this);

    ui->stackedWidget->insertWidget(1,&sw);
    ui->stackedWidget->insertWidget(2,&mw);

    connect(sw.getUi()->multiple_button, SIGNAL(clicked()), this, SLOT(change_stackwidget()));
    connect(mw.getUi()->single_button, SIGNAL(clicked()), this, SLOT(change_stackwidget2()));
}

HistoryMainWidget::~HistoryMainWidget()
{
    delete ui;
}

void HistoryMainWidget::on_single_day_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void HistoryMainWidget::on_multiple_day_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void HistoryMainWidget::change_stackwidget(){
    ui->stackedWidget->setCurrentIndex(2);
}

void HistoryMainWidget::change_stackwidget2(){
    ui->stackedWidget->setCurrentIndex(1);
}
