#include "simulation.h"
#include <algorithm>

//Default constructor
Simulation::Simulation() {
    hiveNumber = 3;
    date = "06.06.19";
}

/**
 * @brief Simulation::Simulation Overloaded constructor
 * @param _hiveNumber hiveNumber
 * @param _date date
 */
Simulation::Simulation(int _hiveNumber, string _date) {
    hiveNumber = _hiveNumber;
    date = _date;
}

// deconstructor
Simulation::~Simulation() {
    sim.clear();
}

//Getters
vector<Message> Simulation::get_sim_vec() {
    return sim;
}

vector<Message> Simulation::get_final_vec() {
    return final;
}

int Simulation::get_size() {
    return size;
}

int Simulation::get_hiveNumber() {
    return hiveNumber;
}

string Simulation::get_date() {
    return date;
}

/**
 * @brief Simulation::process_times Process minutes data into 00:00:00:000 format (hr:min:sec:ms)
 * @param in time
 * @return time in 00:00:00:000 format
 */
string Simulation::process_times(string in) {
    //Turn "." to " "
    replace(in.begin(), in.end(), '.', ' ');

    //Take minutes and decimal values
    stringstream ss(in);
    int mins;
    string dec;
    ss >> mins;
    ss >> dec;

    //Calculate minutes and hours
    int finalMins = mins % 60;
    int finalHrs = mins/60;
    //cout << finalHrs << endl;

    //Calculate seconds and milliseconds
    double secs = 0;
    secs = stod(dec) * 60 / 1000000;

    //cout << secs << endl;
    int finalSecs = int(secs);

    double millisecs = secs - finalSecs;
    int finalMillisecs = int(millisecs * 1000);

    int remainder = finalMillisecs % 50;
    finalMillisecs = finalMillisecs - remainder;

    //Process into string format
    string final = "";
    if ((to_string(finalHrs)).size() == 1) {
        final = final + "0" + to_string(finalHrs) + ".";
    } else if ((to_string(finalHrs)).size() == 2) {
        final = final + to_string(finalHrs) + ".";
    }
    if ((to_string(finalMins)).size() == 1) {
        final = final + "0" + to_string(finalMins) + ".";
    } else if ((to_string(finalMins)).size() == 2) {
        final = final + to_string(finalMins) + ".";
    }
    if ((to_string(finalSecs)).size() == 1) {
        final = final + "0" + to_string(finalSecs);
    } else if ((to_string(finalSecs)).size() == 2) {
        final = final + to_string(finalSecs);
    }
    if ((to_string(finalMillisecs)).size() == 1) {
        final = final + "0" + "0" + to_string(finalMillisecs);
    } else if ((to_string(finalMillisecs)).size() == 2) {
        final = final + "0" + to_string(finalMillisecs);
    } else if ((to_string(finalMillisecs)).size() == 3) {
        final = final + to_string(finalMillisecs);
    }
    return final;
}

/**
 * @brief Simulation::sim_boards Simulate board data for constructing a message
 *                    This needs to be more sophisticated (consider gates entries/exits etc)
 * @param seed seed value
 * @param mins minutes in double
 * @return board message
 */
string Simulation::sim_boards(unsigned int seed, double mins) {
    default_random_engine gen(seed);
    string ret = "";
    string inf;
    //More entries in the first half of the day
    if (mins < 720) {
        for (int i = 0; i < BOARDS; ++i) {
            if (gen() % 10 == 0) {
                inf = to_string(pow(2, (gen() % 7)));
            } else if (gen() % 5 == 1) {
                inf = to_string(pow(2, (gen() % 4)));
            } else if (gen() % 10 == 2) {
                inf = to_string(pow(2, (gen() % 7)) + pow(2, (gen() % 4)));
            } else if (gen() % 5 == 3) {
                inf = to_string(pow(2, (gen() % 4)) + pow(2, (gen() % 4)));
            }
            else if (gen() % 10 == 4) {
                inf = to_string(pow(2, (gen() % 4)) + pow(2, (gen() % 4)) + pow(2, (gen() % 7)));
            } else {
                inf = "0";
            }
            ret = ret + "B" + inf;
        }
    } else {//More exits in the second half of the day
        for (int i = 0; i < BOARDS; ++i) {
            if (gen() % 10 == 0) {
                inf = to_string(pow(2, (gen() % 7)));
            } else if (gen() % 5 == 1) {
                inf = to_string(pow(2, (gen() % 4) + 4));
            } else if (gen() % 10 == 2) {
                inf = to_string(pow(2, (gen() % 7)) + pow(2, (gen() % 4) + 4));
            } else if (gen() % 5 == 3) {
                inf = to_string(pow(2, (gen() % 4) + 4) + pow(2, (gen() % 4) + 4));
            }
            else if (gen() % 10 == 4) {
                inf = to_string(pow(2, (gen() % 4) + 4) + pow(2, (gen() % 4) + 4) + pow(2, (gen() % 7)));
            } else {
                inf = "0";
            }
            ret = ret + "B" + inf;
        }
    }
    return ret;
}

/**
 * @brief Simulation::generate_sim Fills sim vector with generated Messages
 * @param fileName file name
 * @param seed seed value
 */
void Simulation::generate_sim(string fileName, unsigned int seed) {
    default_random_engine gen(seed);
    //Open file specified by input string
    ifstream inFile;
    inFile.open(fileName);

    //Set size (first param given in file)
    inFile >> size;
    //cout << size << endl;

    //Skip other params
    string throwaway;
    for (int i = 0; i < 5; ++i) {
        inFile >> throwaway;
        //cout << throwaway << endl;
    }

    //Store data in vector for sorting
    string in;
    for (int i = 0; i < size; ++i) {
        inFile >> in;
        mins.push_back(stod(in));
    }

    //Sort data
    sort(mins.begin(), mins.end());

    //Process times and simulate random board info
    for (unsigned int i = 0; i < mins.size(); ++i) {
        if (gen() % 20 != 0) {
            string time = process_times(to_string(mins.at(i)));
            //int multHive = (gen() % 3) + 1;
            //Use multHive for multiple hives, or hiveNumber for single
            Message m(hiveNumber, date, time, sim_boards((seed + i), mins.at(i)));
            sim.push_back(m);
            final.push_back(m);
        }
    }

    //Add entries/exits based on board info
    for (unsigned int i = 0; i < sim.size(); ++i) {
        string bds = sim.at(i).get_boards();
        int respHive = sim.at(i).get_hiveNumber();
        //cout << "in board " << bds << endl;
        //Turn "B" to " "
        replace(bds.begin(), bds.end(), 'B', ' ');

        stringstream ss(bds);
        string next;
        string flipped = "";
        for (unsigned int i = 0; i < BOARDS; ++i) {
            ss >> next;
            //Flip all boards and create new B string
            int newBoard = bin_to_dec(flip_bin(dec_to_bin(stoi(next))));
            //Add extra noise for realism
            if (gen() % 10 == 0) {
                newBoard += pow(2, (gen() % 7));
            }
            flipped = flipped + "B" + to_string(newBoard);
        }
        //cout << "out board " << flipped << endl;

        //Create time within a few seconds after initial trigger
        string newTime = sim.at(i).get_time();

        replace(newTime.begin(), newTime.end(), '.', ' ');

        stringstream ss1(newTime);
        string hrs;
        string mins;
        string secs;
        ss1 >> hrs;
        ss1 >> mins;
        ss1 >> secs;
        int intSecs = stoi(secs);
        int intMins = stoi(mins);
        int delta = ((gen() % 50) + 20) * 50;
        intSecs += delta;
        if (intSecs >= 60000) {
            intSecs = intSecs - 60000;
            intMins++;
        }
        mins = to_string(intMins);
        if (mins.length() == 1) {
            mins = "0" + mins;
        }
        secs = to_string(intSecs);
        if (secs.length() == 1) {
            secs = "0000" + secs;
        } else if (secs.length() == 2) {
            secs = "000" + secs;
        } else if (secs.length() == 3) {
            secs = "00" + secs;
        } else if (secs.length() == 4) {
            secs = "0" + secs;
        }
        newTime = hrs + "." + mins + "." + secs;

        //cout << "orig: " << sim.at(i).print_message() << endl;
        if (gen() % 10 != 0) {
            //Use respHive for multiple hives, hiveNumber for single
            Message m1(hiveNumber, date, newTime, flipped);
            //cout << "reac: " << m1.print_message() << endl;
            //Insert m1 into sorted position in sim vector
            for (unsigned int j = i; j < final.size(); ++j) {
                double diff = compare_times(m1.get_time(), final.at(j).get_time());
                if (diff < 0) {
                    //cout << "inserting at: " << j << endl;
                    final.insert(final.begin() + j, m1);
                    break;
                }
            }
        }
    }

    //Close file
    inFile.close();
}

/**
 * @brief Simulation::compare_times Compare times, returns:
 *                    -difference if time1 < time2,
 *                    +difference if time1 > time2,
 *                    0 if time1 = time2
 * @param time1  time 1
 * @param time2 time 2
 * @return time difference
 */
double Simulation::compare_times(string time1, string time2) {
    //Split up times into hr/min/sec components
    replace(time1.begin(), time1.end(), '.', ' ');
    stringstream ss1(time1);
    string hrs1;
    string mins1;
    string secs1;
    ss1 >> hrs1;
    ss1 >> mins1;
    ss1 >> secs1;
    double total1 = (60 * 60 * stod(hrs1)) + (60 * stod(mins1)) + stod(secs1)/1000;
    //cout << total1 << endl;

    replace(time2.begin(), time2.end(), '.', ' ');
    stringstream ss2(time2);
    string hrs2;
    string mins2;
    string secs2;
    ss2 >> hrs2;
    ss2 >> mins2;
    ss2 >> secs2;
    double total2 = (60 * 60 * stod(hrs2)) + (60 * stod(mins2)) + stod(secs2)/1000;
    //cout << total2 << endl;

    return total1 - total2;
}

/**
 * @brief Simulation::dec_to_bin converts decimal to binary
 * @param dec decimal number
 * @return  binary number in string
 */
string Simulation::dec_to_bin(int dec) {
    return bitset<8>(dec).to_string();
}

/**
 * @brief Simulation::bin_to_dec convert binary to decimal
 * @param bin binary number
 * @return decimal number in int
 */
int Simulation::bin_to_dec(string bin) {
    int dec = 0;
    for (unsigned int i = 0; i < bin.length(); ++i) {
        dec += (bin.at(i) - '0') * pow(2, (bin.length() - i - 1));
    }
    return dec;
}

/**
 * @brief Simulation::flip_bin flip the binary number (first goes to last)
 * @param in binary string
 * @return flipped binary string
 */
string Simulation::flip_bin(string in) {
    string out = "";
    for (unsigned int i = 0; i < in.length(); ++i) {
        out.push_back(in.at(in.length() - i - 1));
    }
    return out;
}

