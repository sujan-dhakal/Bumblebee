#ifndef MULTIPLEDAYWIDGET_H
#define MULTIPLEDAYWIDGET_H

#include <QWidget>
#include <iostream>
#include "string.h"

#include "../database/data.h"

namespace Ui {
class MultipleDayWidget;
}

class MultipleDayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleDayWidget(QWidget *parent = nullptr);
    ~MultipleDayWidget();
    Ui::MultipleDayWidget* getUi();

    double findmax(QVector<double> v);

private slots:
    void on_pushButton_clicked();

    void on_zoom_in_button_clicked();

    void on_zoom_out_button_clicked();

    void on_zoom_in_buttony_clicked();

    void on_zoom_out_buttony_clicked();

    void on_up_button_clicked();

    void on_down_button_clicked();

    void on_left_button_clicked();

    void on_right_button_clicked();

private:
    Ui::MultipleDayWidget *ui;
    vector<double> *vx, *vy;
    string startdate;
    string enddate;
    string hiveNumber;
    double minX, maxX;
    double minY, maxY;
};

#endif // MULTIPLEDAYWIDGET_H
