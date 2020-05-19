#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <bitset>

using namespace std;

#define BOARDS 10

class Message {

private:

    //Instance variables
    int hiveNumber;
    string date;
    string time;
    int boards[BOARDS];

public:

    Message();
    Message(int _hiveNumber, string _date, string _time, int _boards[BOARDS]);
    Message(int _hiveNumber, string _date, string _time, string _boards);
    ~Message();

    //Getters
    int get_hiveNumber();
    string get_date();
    string get_time();
    string get_boards();

    //Setters
    void set_hiveNumber(int _hiveNumber);
    void set_date(string _date);
    void set_time(string _time);
    void set_boards(int arr[BOARDS]);

    //Print UDP message
    string print_message();

};

#endif // MESSAGE_H
