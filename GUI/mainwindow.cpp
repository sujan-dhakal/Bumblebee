#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->stackedWidget->insertWidget(1,&curr);
    ui->stackedWidget->insertWidget(2,&hmw);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_live_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_historical_button_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_actionHome_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionExit_triggered()
{
   close();
}
