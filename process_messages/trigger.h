#ifndef TRIGGER_H
#define TRIGGER_H

#include <iostream>

using namespace std;

#define BOARDS 10
#define GATES 8

class Trigger {

private:

    //Instance variables
    int hiveNumber;
    string date;
    double time;
    int boardNumber;
    int gateNumber;

public:

    //Constructors and destructor
    Trigger();
    Trigger(int _hiveNumber, string _date, double _time, int _boardNumber, int _gateNumber);
    ~Trigger();

    //Getters
    double get_time();
    string get_date();
    void set_time(double _time);
    int get_hiveNumber();
    int get_boardNumber();
    int get_gateNumber();

    //Overloaded operators
    bool operator<(Trigger t) const;
    bool operator>(Trigger t) const;
    bool operator==(Trigger t) const;

    //To string
    string print_trigger();
};

#endif // TRIGGER_H
