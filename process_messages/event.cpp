#include "event.h"

// Default constructor
Event::Event() {

}

/**
 * @brief Event::Event Overloaded constructor
 * @param _type entry or exit
 * @param _time time
 * @param _date date
 * @param _hiveNumber hive number
 * @param _boardNumber board number
 */
Event::Event(string _type, double _time, string _date, int _hiveNumber, int _boardNumber) {
    type = _type;
    time = _time;
    date = _date;
    hiveNumber = _hiveNumber;
    boardNumber = _boardNumber;
}

// deconstructor
Event::~Event() {
}

//Getters
double Event::get_time_double() {
    return time;
}

string Event::get_time() {
    return format_time();
}

string Event::get_date() {
    return date;
}

string Event::get_type() {
    return type;
}

int Event::get_hiveNumber() {
    return hiveNumber;
}

int Event::get_boardNumber() {
    return boardNumber;
}

//Setters
void Event::set_time(double _time) {
    time = _time;
}

void Event::set_date(string _date) {
    date = _date;
}

void Event::set_type(string _type) {
    type = _type;
}

void Event::set_hiveNumber(int _hiveNumber) {
    hiveNumber = _hiveNumber;
}

void Event::set_boardNumber(int _boardNumber) {
    boardNumber = _boardNumber;
}

void Event::set_stime(string _stime){
    stime= _stime;
}

string Event::get_stime(){
    return stime;
}

/**
 * @brief Event::format_time Turn time from seconds.milliseconds
 * @return time in required format
 */
string Event::format_time() {
    string ret = "";
    int totalSecs = time;
    int furtherMillisecs = (time * 1000) - (totalSecs * 1000);
    int totalHrs = totalSecs / (60 * 60);
    string totalHrsS = to_string(totalHrs);
    if (totalHrsS.size() == 1) {
        totalHrsS = "0" + totalHrsS;
    }
    int furtherMins =  (totalSecs - (totalHrs * 60 * 60)) / 60;
    string furtherMinsS = to_string(furtherMins);
    if (furtherMinsS.size() == 1) {
        furtherMinsS = "0" + furtherMinsS;
    }
    int furtherSecs = (totalSecs - (totalHrs * 60 * 60) - (furtherMins * 60));
    int totalFurtherMillisecs = (furtherSecs * 1000) + furtherMillisecs;
    string furtherMillisecsS = to_string(totalFurtherMillisecs);
    if (furtherMillisecsS.size() == 3) {
        furtherMillisecsS = "00" + furtherMillisecsS;
    } else if (furtherMillisecsS.size() == 4) {
        furtherMillisecsS = "0" + furtherMillisecsS;
    } else if (furtherMillisecsS.size() == 1) {
        furtherMillisecsS = "0000" + furtherMillisecsS;
    }
    ret = ret + totalHrsS + "." + furtherMinsS + "." + furtherMillisecsS;
    return ret;
}

/**
 * @brief Event::print_event print events
 * @return
 */
string Event::print_event() {
    string ret = type + " from hive ";
    ret = ret + to_string(hiveNumber);
    ret = ret + " board";
    ret = ret + to_string(boardNumber);
    ret = ret + " on ";
    ret = ret + date;
    ret = ret + " at ";
    ret = ret + format_time();
    return ret;
}
