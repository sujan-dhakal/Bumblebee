#ifndef SINGLEDAYDATA_H
#define SINGLEDAYDATA_H

#include <QDialog>

#include "../process_messages/event.h"
#include "../process_messages/parse.h"

namespace Ui {
class Singledaydata;
}

class Singledaydata : public QDialog
{
    Q_OBJECT

public:
    explicit Singledaydata(QWidget *parent = nullptr);
    ~Singledaydata();
    void replot();
    void fill_events();
    void count_events();

private slots:

    void on_move_left_clicked();
    void on_move_right_clicked();

    //void on_ok_button_clicked();

private:

    Ui::Singledaydata *ui;
    std::vector<double> *vx, *vy;
    double minX, maxX, incrX;
    vector<Event> vec;
    int arr [100];

};

#endif // SINGLEDAYDATA_H
