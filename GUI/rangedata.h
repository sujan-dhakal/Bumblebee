#ifndef RANGEDATA_H
#define RANGEDATA_H

#include <QDialog>

#include "../process_messages/event.h"
#include "../process_messages/parse.h"

namespace Ui {
class RangeData;
}

class RangeData : public QDialog
{
    Q_OBJECT

public:
    explicit RangeData(QWidget *parent = nullptr);
    ~RangeData();
    void replot();
    void fill_events();

private slots:

    void on_move_left_clicked();
    void on_move_right_clicked();

    //void on_ok_button_clicked();

private:
    Ui::RangeData *ui;
    std::vector<double> *vx, *vy;
    double minX, maxX, incrX;
    vector<Event> vec;
};

#endif // RANGEDATA_H
