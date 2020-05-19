#ifndef PARSE_H
#define PARSE_H

#include "event.h"
#include "trigger.h"

#include "../database/dbtool.h"
#include "../database/dbtable.h"
#include "../database/dbevent.h"
#include "../database/dbudp.h"

#define DIFF 5

class Parse {

private:

    //Instance variables
    string fileName;
    vector<Trigger> trigs;
    vector<Event> activity;
    DBTool *dbtool;
    DBudp *udptable;
    DBEvent *eventtable;

public:

    //Constructors and destructor
    Parse();
    Parse(string _fileName);
    ~Parse();

    //Getters
    vector<Event> get_activity();

    //Methods
    void read_activity(string fileName);
    void create_events();
    string dec_to_bin(int dec);

    string format_date_DB(string date);

    void print_activity();

};

#endif // PARSE_H
