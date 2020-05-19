#include "parse.h"
#include "algorithm"
#include "bitset"

//default constructor
Parse::Parse() {

}

/**
 * @brief Parse::Parse overloaded constructor
 * @param _fileName file Name
 */
Parse::Parse(string _fileName) {
    fileName = _fileName;
}

// deconstructor
Parse::~Parse() {
    trigs.clear();
    activity.clear();
    dbtool->~DBTool();
}

//Getters
vector<Event> Parse::get_activity() {
    return activity;
}


/**
 * @brief Parse::read_activity Creates trigger objects for all gate triggers
 * @param fileName file name
 */
void Parse::read_activity(string fileName) {
    //Read input from given file name
    ifstream inFile;
    inFile.open(fileName);
    string UDP;

    dbtool = new DBTool("BumblebeeDB");
    dbtool->print(std::cout);
    udptable= new DBudp(dbtool, "TableUDP");
    eventtable = new DBEvent(dbtool, "TableEvent");

    while (inFile >> UDP) {
        udptable->add_row(UDP);
        //Process all gate triggers
        replace(UDP.begin(), UDP.end(), '-', ' ');// replaces - with ' '
        stringstream ss(UDP);

        string hive;
        ss >> hive;
        int hiveNumber = stoi(hive.substr(2, hive.size() - 2));
        string dateTime;
        ss >> dateTime;
        string date = dateTime.substr(1,8);
        string time = dateTime.substr(10, 20);
        string allBoards;
        ss >> allBoards;

        //Process individual boards
        replace(allBoards.begin(), allBoards.end(), 'B', ' ');
        stringstream ssb(allBoards);
        for (unsigned int i = 0; i < BOARDS; ++i) {
            int board;
            ssb >> board;
            if (board != 0) {
                //Make time a double for Trigger constructor
                string newTime = time;
                replace(newTime.begin(), newTime.end(), '.', ' ');
                stringstream sst(newTime);
                double hrs;
                double mins;
                string other;
                sst >> hrs;
                sst >> mins;
                sst >> other;
                string secs = other.substr(0, 2);
                string millisecs = other.substr(2, 5);
                double dsecs = stod(secs + "." + millisecs);
                double totalTime = (60 * 60 * hrs) + (60 * mins) + dsecs;

                string binBoard = dec_to_bin(board);
                for (unsigned int j = 0; j < 8; ++j) {
                    if (binBoard.at(j) == '1') {
                        Trigger t(hiveNumber, date, totalTime, i, GATES - j);
                        //t.print_trigger();
                        trigs.push_back(t);
                    }
                }
            }
        }

    }
    //cout << trigs.size() << endl;
    inFile.close();
    eventtable->select_all();
}


/**
 * @brief Parse::create_events Search through given time window to create Events
 */
void Parse::create_events() {
    //Look through each trigger
    for (unsigned int i = 0; i < trigs.size(); ++i) {
        //End if we're at the last set of triggers
        if (trigs.at(i).get_time() == trigs.at(trigs.size() - 1).get_time()) {
            break;
        }
        //Take initial trigger information
        int currBoard = trigs.at(i).get_boardNumber();
        int currGate = trigs.at(i).get_gateNumber();
        int oppGate = GATES + 1 - currGate;
        double currTime = trigs.at(i).get_time();
        //Make variable to maintain a window of time
        double timeDiff = 0;
        //Assign j to the next trigger of a different time
        unsigned int j = 1;
        bool sameTime = true;
        while (sameTime == true) {
            Trigger t = trigs.at(i + j);
            if (t.get_time() != trigs.at(i).get_time()) {
                sameTime = false;
            }
            ++j;
        }
        --j;
        //Check later triggers within the given window of time DIFF
        while ((timeDiff < DIFF) && ((i + j) < trigs.size() - 1)) {
            Trigger t1 = trigs.at(i + j);
            //Check if a trigger is from the opposite gate on the same board
            if ((t1.get_boardNumber() == currBoard) && (t1.get_gateNumber() == oppGate)) {
                //In to out is an exit
                if (currGate <= GATES/2) {
                    Event exit("Exit", t1.get_time(), t1.get_date(), t1.get_hiveNumber(), t1.get_boardNumber());
                    //Insert sorted into activity vector (by time)
                    unsigned int k = 1;
                    bool inserted = false;
                    while (inserted == false) {
                        if (activity.size() == 0) {
                            activity.push_back(exit);
                            eventtable->add_row(format_date_DB(exit.get_date()), exit.get_time(), exit.get_hiveNumber(), exit.get_boardNumber(), exit.get_type());
                            inserted = true;
                        }
                        if ((activity.at(activity.size() - k)).get_time_double() > exit.get_time_double()) {
                            activity.insert(activity.begin() + activity.size() - k, exit);
                            eventtable->add_row(format_date_DB(exit.get_date()), exit.get_time(), exit.get_hiveNumber(), exit.get_boardNumber(), exit.get_type());
                            inserted = true;
                        } else {
                            activity.push_back(exit);
                            eventtable->add_row(format_date_DB(exit.get_date()), exit.get_time(), exit.get_hiveNumber(), exit.get_boardNumber(), exit.get_type());
                            inserted = true;
                        }
                        ++k;
                    }
                    trigs.erase(trigs.begin() + i + j);
                    break;
                } else { //Out to in is an entry
                    Event entry("Entry", t1.get_time(), t1.get_date(), t1.get_hiveNumber(), t1.get_boardNumber());
                    //Insert sorted into activity vector (by time)
                    unsigned int k = 1;
                    bool inserted = false;
                    while (inserted == false) {
                        if (activity.size() == 0) {
                            activity.push_back(entry);
                            eventtable->add_row(format_date_DB(entry.get_date()), entry.get_time(), entry.get_hiveNumber(), entry.get_boardNumber(), entry.get_type());
                            inserted = true;
                        }
                        if ((activity.at(activity.size() - k)).get_time_double() > entry.get_time_double()) {
                            activity.insert(activity.begin() + activity.size() - k, entry);
                            eventtable->add_row(format_date_DB(entry.get_date()), entry.get_time(), entry.get_hiveNumber(), entry.get_boardNumber(), entry.get_type());
                            inserted = true;
                        } else {
                            activity.push_back(entry);
                            eventtable->add_row(format_date_DB(entry.get_date()), entry.get_time(), entry.get_hiveNumber(), entry.get_boardNumber(), entry.get_type());
                            inserted = true;
                        }
                        ++k;
                    }

                    trigs.erase(trigs.begin() + i + j);
                    break;
                }
            }
            //Increase the time difference window
            timeDiff = trigs.at(i + j + 1).get_time() - currTime;
            j++;
        }
    }
}

/**
 * @brief Parse::print_activity print activity
 */
void Parse::print_activity() {
    for (Event e : activity) {
        cout << e.print_event() << endl;
    }
    cout << "Total number of events: " << activity.size() << endl;
}

/**
 * @brief Parse::dec_to_bin convert decimal to binary
 * @param dec decimal number
 * @return binary string
 */
string Parse::dec_to_bin(int dec) {
    return bitset<8>(dec).to_string();
}

/**
 * @brief Parse::format_date_DB formate date in YY/MM/DD
 * @param date date
 * @return  date in YY/MM/DD
 */
string Parse::format_date_DB(string date) {
    replace(date.begin(), date.end(), '.', ' ');
    stringstream ss(date);
    string day;
    string month;
    string year;
    ss >> day;
    ss >> month;
    ss >> year;
    string ret = year + "." + month + "." + day;
    return ret;
}
