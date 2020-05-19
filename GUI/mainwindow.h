#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "singleday_widget.h"
#include "current_widget.h"
#include "historymainwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_live_button_clicked();

    void on_historical_button_clicked();

    void on_actionHome_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    current_widget curr;
    HistoryMainWidget hmw;
};

#endif // MAINWINDOW_H
