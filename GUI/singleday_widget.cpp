#include "singleday_widget.h"
#include "ui_singleday_widget.h"

singleday_widget::singleday_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singleday_widget)
{
    ui->setupUi(this);
}

singleday_widget::~singleday_widget()
{
    delete ui;
}

Ui::singleday_widget* singleday_widget::getUi(){
    return ui;
};

/**
 * @brief singleday_widget::on_pushButton_clicked plot graph after pressing OK
 */
void singleday_widget::on_pushButton_clicked(){
    date=ui->dateEditor->text().toStdString();
    hiveNumber=ui->hive_num->text().toStdString();
    QVector<double> x(24), y(24);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    for (int i=0; i<24; i++){
        x[i]=i;
    }
    textTicker->addTick(0,  "12am");
    textTicker->addTick(2,  "2am");
    textTicker->addTick(5,  "5am");
    textTicker->addTick(8,  "8am");
    textTicker->addTick(11,  "11am");
    textTicker->addTick(14,  "2pm");
    textTicker->addTick(17,  "5pm");
    textTicker->addTick(20,  "8pm");
    textTicker->addTick(23,  "11pm");
    ui->nest->xAxis->setTicker(textTicker);

    Data d("../../../../process_messages");
    d.selectwhereData(date, date, hiveNumber);
    int counter=0;
    int tj=0;
    for (int i=0; i<d.getEventsV().size(); i++){
        string t= d.getEventsV().at(i).get_stime();
        replace(t.begin(), t.end(), '.', ' ');
        stringstream time(t);
        string hour;
        time>>hour;
        int h= stoi(hour, nullptr, 10);
        if (h==tj){
            counter++;
            if (i==d.getEventsV().size()-1){
                y[tj]=counter;
                while (tj<23){
                    tj++;
                    y[tj]=0;
                }
            }
        } else{
            y[tj]=counter;
            tj++;
            counter=0;
            if (i==0){
                i=0;
            } else {
                i--;
            }
        }
    }

    ui->nest->addGraph();
    ui->nest->graph(0)->setData(x,y);
    // give the axes some labels:
    ui->nest->xAxis->setLabel("Time");
    ui->nest->yAxis->setLabel("Activity (Entries+Exits)");
    // set axes ranges, so we see the data:
    minX=0;
    maxX=12;
    minY=0;
    maxY=(findmax(y)*3)/4;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

/**
 * @brief singleday_widget::findmax find the max value of vector
 * @param y vector
 * @return max value
 */
double singleday_widget::findmax(QVector<double> y){
    double max=0;
    for (int i=0; i<y.size(); i++){
        if (y.at(i)>max){
            max=y.at(i);
        }
    }
    return max;
}

void singleday_widget::on_zoom_in_button_clicked(){
    minX=minX+1;
    maxX=maxX-1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void singleday_widget::on_zoom_out_button_clicked(){
    minX=minX-1;
    maxX=maxX+1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void singleday_widget::on_right_button_clicked(){
    minX=minX+1;
    maxX=maxX+1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void singleday_widget::on_left_button_clicked(){
    minX=minX-1;
    maxX=maxX-1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void singleday_widget::on_zoom_in_buttony_clicked(){
    minY=minY+4;
    maxY=maxY-4;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void singleday_widget::on_zoom_out_buttony_clicked(){
    minY=minY-4;
    maxY=maxY+4;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void singleday_widget::on_up_button_clicked(){
    minY=minY+4;
    maxY=maxY+4;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void singleday_widget::on_down_button_clicked(){
    minY=minY-4;
    maxY=maxY-4;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}
