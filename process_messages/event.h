#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

#define BOARDS 10
#define GATES 8

class Event {

    //Instance variables
    double time;
    string stime;
    string date;
    string type;
    int hiveNumber;
    int boardNumber;

public:

    //Constructors and destructor
    Event();
    Event(string _type, double _time, string _date, int _hiveNumber, int _boardNumber);
    ~Event();

    //Getters
    double get_time_double();
    string get_time();
    string get_stime();
    string get_date();
    string get_type();
    int get_hiveNumber();
    int get_boardNumber();

    //Setters
    void set_stime(string _stime);
    void set_time(double _time);
    void set_date(string _date);
    void set_type(string _type);
    void set_hiveNumber(int _hiveNumber);
    void set_boardNumber(int _boardNumber);

    string format_time();
    string print_event();

};

#endif // EVENT_H
