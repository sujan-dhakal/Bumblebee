#include "rangedata.h"
#include "ui_rangedata.h"

RangeData::RangeData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RangeData)
{
    ui->setupUi(this);
    minX = 0;
    maxX = 86400;
    incrX = 0.05;
    // generate some data:
    vx = new std::vector<double>();
    vy = new std::vector<double>();
    QVector<double> x(101), y(101);

    // initialize with entries 0..100
    for (int i = 0; i < vec.size(); i = i + 10)
    {
      vx->push_back(vec.at(i).get_time_double());
      x[i] = i/50.0 - 1; // x goes from
      vy->push_back(1);
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    // create graph and assign data to it:
    ui->nest->addGraph();
    ui->nest->graph(0)->setData(x, y);

    // give the axes some labels:
    ui->nest->xAxis->setLabel("Time");
    ui->nest->yAxis->setLabel("Events");

    // set axes ranges, so we see the data:
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->yAxis->setRange(0, 100);
    ui->nest->replot();
}

RangeData::~RangeData()
{
    delete ui;
    delete vx;
    delete vy;
}

void RangeData::replot(){
    QVector<double> x(int(vx->size())), y(int(vx->size()));
    for (unsigned long i = 0; i < vx->size(); i++){
      x[int(i)] = vx->at(i); // update x
      y[int(i)] = vy->at(i); // update y
    }
    // reassign data:
    ui->nest->graph(0)->setData(x, y);
    ui->nest->replot();
}

// Decrease minX, maxX to move to left of graph
void RangeData::on_move_left_clicked(){
    minX = minX - 0.05;
    maxX = maxX - 0.05;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

// Increase minX, maxX to move to right of graph
void RangeData::on_move_right_clicked(){
    minX = minX + 0.05;
    maxX = maxX + 0.05;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void RangeData::fill_events() {
    Parse p;
    p.read_activity("UDP_messages_data_1.txt");
    p.create_events();
    vec = p.get_activity();
}

//void Historical::on_ok_button_clicked()
//{
//    // Get coordinate from text field
//    QString x_line = ui->x_line->text();
//    double x_coor = x_line.toDouble();
//    QString y_line = ui->y_line->text();
//    double y_coor = y_line.toDouble();

//    // Save new coordinate to x,y vectors
//    vx->push_back(x_coor);
//    vy->push_back(y_coor);

//    // Initialize and copy all coordinates to 2 QVectors
//    QVector<double> x(vx->size()), y(vy->size());
//    for (unsigned i=0; i<vx->size(); ++i)
//    {
//      x[i] = vx->at(i); // x goes from -1 to 1
//      y[i] = vy->at(i); // let's plot a quadratic function
//    }

//    // Draw new data with new coordinates
//    ui->nest->graph(0)->setData(x, y);
//    ui->nest->replot();

//}
