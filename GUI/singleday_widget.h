#ifndef SINGLEDAY_WIDGET_H
#define SINGLEDAY_WIDGET_H

#include <QWidget>
#include <iostream>
#include "string.h"

#include "../database/data.h"

using namespace std;

namespace Ui {
class singleday_widget;
}

class singleday_widget : public QWidget
{
    Q_OBJECT

public:
    explicit singleday_widget(QWidget *parent = nullptr);
    ~singleday_widget();
    Ui::singleday_widget* getUi();
    double findmax(QVector<double> y);

private slots:
    void on_pushButton_clicked();

    void on_zoom_in_button_clicked();

    void on_zoom_out_button_clicked();

    void on_right_button_clicked();

    void on_left_button_clicked();

    void on_zoom_in_buttony_clicked();

    void on_zoom_out_buttony_clicked();

    void on_up_button_clicked();

    void on_down_button_clicked();

private:
    Ui::singleday_widget *ui;
    string date;
    string hiveNumber;
    double minX, maxX;
    double minY, maxY;

};

#endif // SINGLEDAY_WIDGET_H
