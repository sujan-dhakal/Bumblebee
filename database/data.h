#ifndef DATA_H
#define DATA_H

#include <iostream>

#include "../process_messages/event.h"
class Event;

#include "dbtool.h"
class DBTool;

#include "dbtable.h"
class DBTable;

#include "dbevent.h"
class DBEvent;

#include "dbudp.h"
class DBudp;

class Data
{
public:
    Data();
    Data(string location);
    ~Data();

    void construct_data(int size, char **d, char **colNames);
    void printData();
    void selectallData();
    void selectwhereData(string startdate, string enddate, string hiveNumber);
    void selectwheredtt(string date, string starttime, string endtime, string hiveNumber, string type);

    vector<Event> getEventsV();

private:
    DBTool *dbtool;
    DBEvent *tableevent;
    vector <Event> events;
};

#endif // DATA_H
