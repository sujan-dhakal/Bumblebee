#include "trigger.h"

// default constructor
Trigger::Trigger() {

}

/**
 * @brief Trigger::Trigger Overloaded constructor
 * @param _hiveNumber hive number
 * @param _date date
 * @param _time time
 * @param _boardNumber board number
 * @param _gateNumber date number
 */
Trigger::Trigger(int _hiveNumber, string _date, double _time, int _boardNumber, int _gateNumber) {
    hiveNumber = _hiveNumber;
    date = _date;
    time = _time;
    boardNumber = _boardNumber;
    gateNumber = _gateNumber;
}

// deconstructor
Trigger::~Trigger() {

}

// setter and getters
void Trigger::set_time(double _time)
{
    time = _time;
}

double Trigger::get_time() {
    return time;
}

string Trigger::get_date() {
    return date;
}

int Trigger::get_hiveNumber() {
    return hiveNumber;
}

int Trigger::get_boardNumber() {
    return boardNumber;
}

int Trigger::get_gateNumber() {
    return gateNumber;
}

// operator overloaders
bool Trigger::operator<(Trigger t) const
{
    if(time < t.time) return true;
    return false;
}

bool Trigger::operator>(Trigger t) const
{
    if(time > t.time) return true;
    return false;
}

bool Trigger::operator==(Trigger t) const
{
    if(time == t.time) return true;
    return false;
}

/**
 * @brief Trigger::print_trigger get gate triggers
 * @return triggers
 */
string Trigger::print_trigger() {
    string ret = "HC";
    ret = ret + to_string(hiveNumber);
    ret = ret + "-D";
    ret = ret + date;
    ret = ret + "T";
    ret = ret + to_string(time) + "-B";
    ret = ret + to_string(boardNumber);
    ret = ret + "-G" + to_string(gateNumber);
    return ret;
}

