#include <iostream>

#include "simulation.h"

using namespace std;

int main() {

    cout <<endl<<"Hello From Bumblebee."<<endl<<endl;

    // Uncomment This Code to generate data

//    //Simulation UDP messages
//    for (int i = 30; i < 31; ++i) {
//        string date = to_string(i);
//        date = date + ".04.19";
//        Simulation s(3, date);
//        string file = "1day_test_data_" + to_string((i % 5) + 1);
//        file = file + ".txt";
//        s.generate_sim(file, 1000 + (30 + i));

//        ofstream outFile;
//        string file2 = "1day_test_UDP_" + to_string(i);
//        file2 = file2 + ".txt";
//        outFile.open(file2);

//        for (Message m : s.get_final_vec()) {
//            outFile << m.print_message() << endl;
//            //cout << m.print_message() << endl;
//        }
//        //cout << "Total: " << s.get_final_vec().size() << endl;
//        outFile.close();
//    }

    return 0;
}
