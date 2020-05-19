#ifndef HISTORYMAINWIDGET_H
#define HISTORYMAINWIDGET_H

#include <QWidget>
#include "singleday_widget.h"
#include "ui_singleday_widget.h"
#include "multipledaywidget.h"
#include "ui_multipledaywidget.h"


namespace Ui {
class HistoryMainWidget;
}

class HistoryMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryMainWidget(QWidget *parent = nullptr);
    ~HistoryMainWidget();

private slots:
    void on_single_day_clicked();

    void on_multiple_day_clicked();

    void change_stackwidget();
    void change_stackwidget2();


private:
    Ui::HistoryMainWidget *ui;
    singleday_widget sw;
    MultipleDayWidget mw;


};

#endif // HISTORYMAINWIDGET_H
