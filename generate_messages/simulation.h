#ifndef SIMULATION_H
#define SIMULATION_H

#include "message.h"

class Simulation {

private:

    vector<double> mins;
    vector<Message> sim;
    vector<Message> final;
    int size;
    int hiveNumber;
    string date;

public:

    //Constructors and destructor
    Simulation();
    Simulation(int _hiveNumber, string _date);
    ~Simulation();

    //Getters
    vector<Message> get_sim_vec();
    vector<Message> get_final_vec();
    int get_size();
    int get_hiveNumber();
    string get_date();

    string process_times(string in);
    string sim_boards(unsigned int seed, double mins);
    void generate_sim(string fileName, unsigned int seed);

    double compare_times(string time1, string time2);

    string dec_to_bin(int dec);
    int bin_to_dec(string dec);
    string flip_bin(string in);

};

#endif // SIMULATION_H
