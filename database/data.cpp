#include "data.h"

// Default Constructor
Data::Data()
{
    dbtool = new DBTool("../process_messages", "BumblebeeDB");
    tableevent= new DBEvent(dbtool, "TableEvent");
}

/**
 * @brief Data::Data overloaded constructor
 * @param location
 */
Data::Data(string location){
    dbtool = new DBTool(location, "BumblebeeDB");
    tableevent= new DBEvent(dbtool, "TableEvent");
}

// deconstructor
Data::~Data(){

}

/**
 * @brief Data::selectallData Select all the event data from database (works through SQlite Query)
 */
void Data::selectallData(){
    tableevent->set_data(this);
    tableevent->select_all();
}

/**
 * @brief Data::selectwhereData select event data based on given parameters (sqlite query)
 * @param startdate start date
 * @param enddate ending date
 * @param hiveNumber hive number
 */
void Data::selectwhereData(string startdate, string enddate, string hiveNumber){
    tableevent->set_data(this);
    tableevent->select_where(startdate, enddate, hiveNumber);
}

/**
 * @brief Data::selectwheredtt Select event data based on given parameter (sqlite query)
 * @param date date
 * @param starttime starting time
 * @param endtime ending time
 * @param hiveNumber hive number
 * @param type entry/ exit
 */
void Data::selectwheredtt(string date, string starttime, string endtime, string hiveNumber, string type){
    tableevent->set_data(this);
    tableevent->select_wheredtt(date, starttime, endtime, hiveNumber, type);
}

/**
 * @brief Data::construct_data fill the data extracted from query to the vector of events
 * @param size table size
 * @param d data
 * @param colNames coloum Names
 */
void Data::construct_data(int size, char **d, char **colNames){
    string date= string(d[0]);
    string time= string(d[1]);
    int hiveNumber= atoi(d[2]);
    int boardNumber= atoi(d[2]);
    string type= string(d[4]);
    Event e;
    e.set_date(date);
    e.set_stime(time);
    e.set_hiveNumber(hiveNumber);
    e.set_boardNumber(boardNumber);
    e.set_type(type);
    events.push_back(e);
}

/**
 * @brief Data::printData print the vector events
 */
void Data::printData(){
    for (unsigned i=0; i<events.size(); i++){
        cout<<events.at(i).get_date()<<" "<< events.at(i).get_stime()<<" " <<events.at(i).get_hiveNumber()<< " " <<events.at(i).get_type()<<endl;
    }
}

/**
 * @brief Data::getEventsV get the vector of events
 * @return
 */
vector<Event> Data::getEventsV(){
    return events;
}
