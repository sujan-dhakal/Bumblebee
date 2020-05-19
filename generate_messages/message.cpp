#include "message.h"
#include "algorithm"

// Default constructor
Message::Message() {

}

/**
 * @brief Message::Message Overloaded constructor
 * @param _hiveNumber hive number
 * @param _date date
 * @param _time time
 * @param _boards array of boards
 */
Message::Message(int _hiveNumber, string _date, string _time, int _boards[BOARDS]) {
    //Set appropriately
    hiveNumber = _hiveNumber;
    date = _date;
    time = _time;
    for (unsigned int i = 0; i < BOARDS; ++i) {
        boards[i] = _boards[i];
    }
}

/**
 * @brief Message::Message Overloaded constructor
 * @param _hiveNumber hive number
 * @param _date date
 * @param _time time
 * @param _boards boards as string
 */
Message::Message(int _hiveNumber, string _date, string _time, string _boards) {
    //Set appropriately
    hiveNumber = _hiveNumber;
    date = _date;
    time = _time;
    //Turn "B" to " "
    replace(_boards.begin(), _boards.end(), 'B', ' ');

    stringstream ss(_boards);
    string decCode;
    for (unsigned int i = 0; i < BOARDS; ++i) {
        ss >> decCode;
        boards[i] = stoi(decCode);
    }
}

// Deconstructor
Message::~Message() {

}

//Getters
int Message::get_hiveNumber() {
    return hiveNumber;
}

string Message::get_date() {
    return date;
}

string Message::get_time() {
    return time;
}

string Message::get_boards() {
    string ret = "";
    for (unsigned int i = 0; i < BOARDS; ++i) {
        ret = ret + "B";
        ret = ret + (to_string(boards[i]));
    }
    return ret;
}

//Setters
void Message::set_hiveNumber(int _hiveNumber) {
    hiveNumber = _hiveNumber;
}

void Message::set_date(string _date) {
    date = _date;
}

void Message::set_time(string _time) {
    time = _time;
}

void Message::set_boards(int arr[BOARDS]) {
    for (unsigned int i = 0; i < BOARDS; ++i) {
        boards[i] = arr[i];
    }
}

/**
 * @brief Message::print_message print UDP messages
 * @return UDP messages
 */
string Message::print_message() {
    string ret = "HC";
    ret = ret + to_string(hiveNumber);
    ret = ret + "-D";
    ret = ret + date;
    ret = ret + "T";
    ret = ret + time + "-";
    for (unsigned int i = 0; i < BOARDS; ++i) {
        ret = ret + "B";
        ret = ret + to_string(boards[i]);
    }
    return ret;
}
