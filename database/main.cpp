#include <iostream>

#include "dbtool.h"
#include "dbudp.h"
#include "dbevent.h"
#include "data.h"



using namespace std;

int main()
{
    Data d;
    d.selectallData();
    d.printData();

    //Place desired startDate, endDate and hiveNumber (all strings) below
    //d.selectwhereData("19.06.02", "19.06.02", "1");
    //d.printData();

    //d.selectwheredtt("19.03.28", "03.00.00000", "03.59.59999", "1", "Entry");
    //d.selectwheredtt("19.03.28", "03.00.00000", "03.59.59999", "1", "Exit");
    //d.printData();

    return 0;
}
