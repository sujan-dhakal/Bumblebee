#include "multipledaywidget.h"
#include "ui_multipledaywidget.h"

MultipleDayWidget::MultipleDayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultipleDayWidget)
{
    ui->setupUi(this);
}

MultipleDayWidget::~MultipleDayWidget()
{
    delete ui;
    delete vx;
    delete vy;
}

Ui::MultipleDayWidget* MultipleDayWidget::getUi(){
    return ui;
};

/**
 * @brief MultipleDayWidget::on_pushButton_clicked draws graph after pressing OK button
 */
void MultipleDayWidget::on_pushButton_clicked()
{
    startdate=ui->startdate->text().toStdString();
    enddate=ui->enddate->text().toStdString();
    hiveNumber=ui->hivenum->text().toStdString();

    Data d("../../../../process_messages");
    d.selectwhereData(startdate, enddate, hiveNumber);
    vx= new vector<double>();
    vy= new vector<double>();
    int counter=0;
    int j=1;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    if (d.getEventsV().size()!=0){
        string da=d.getEventsV().at(0).get_date();
        textTicker->addTick(1,  da.c_str());
        for (int i=0; i<d.getEventsV().size(); i++){
            string da2=d.getEventsV().at(i).get_date();
            if (da==da2){
                counter++;
                if (i==d.getEventsV().size()-1){
                    vx->push_back(j);
                    vy->push_back(counter);
                    da=d.getEventsV().at(i).get_date();
                    textTicker->addTick(j,  da.c_str());
                }
            } else {
                vx->push_back(j);
                if (j!=1){
                    textTicker->addTick(j, da.substr(6,7).c_str());
                }
                vy->push_back(counter);
                counter=1;
                da=d.getEventsV().at(i).get_date();
                j++;
            }
        }
    }
    ui->nest->xAxis->setTicker(textTicker);

    QVector <double> x(vx->size()), y(vy->size());
    for (int i=0; i<vx->size(); i++){
        x[i]=vx->at(i);
        y[i]=vy->at(i);
    }
    ui->nest->addGraph();
    ui->nest->graph(0)->setData(x,y);
    ui->nest->xAxis->setLabel("Days (YY/MM/DD)");
    ui->nest->yAxis->setLabel("Activity (Entries+Exits)");
    // set axes ranges, so we see the data:
    minX=0;
    maxX=5;
    minY=0;
    maxY=findmax(y)-20;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

/**
 * @brief MultipleDayWidget::findmax find the maximum value of vector
 * @param v vector
 * @return max value
 */
double MultipleDayWidget::findmax(QVector<double> v){
    double max=0;
    for (int i=0; i<v.size(); i++){
        if (v.at(i)>max){
            max=v.at(i);
        }
    }
    return max;
}

void MultipleDayWidget::on_zoom_in_button_clicked(){
    minX=minX+1;
    maxX=maxX-1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void MultipleDayWidget::on_zoom_out_button_clicked(){
    minX=minX-1;
    maxX=maxX+1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void MultipleDayWidget::on_zoom_in_buttony_clicked(){
    minY=minY+10;
    maxY=maxY-10;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void MultipleDayWidget::on_zoom_out_buttony_clicked(){
    minY=minY-10;
    maxY=maxY+10;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void MultipleDayWidget::on_up_button_clicked(){
    minY=minY+10;
    maxY=maxY+10;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void MultipleDayWidget::on_down_button_clicked(){
    minY=minY-10;
    maxY=maxY-10;
    ui->nest->yAxis->setRange(minY, maxY);
    ui->nest->replot();
}

void MultipleDayWidget::on_left_button_clicked(){
    minX=minX-1;
    maxX=maxX-1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}

void MultipleDayWidget::on_right_button_clicked(){
    minX=minX+1;
    maxX=maxX+1;
    ui->nest->xAxis->setRange(minX, maxX);
    ui->nest->replot();
}
