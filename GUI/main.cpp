/*********************************************************************

Copyright (C) 2019 Sujan Dhakal, Utsav Shrestha, Ben Chaplin and Sorawit Roongruengratanakul

This program is not a free software: you cannot redistribute it and/or modify
it under any terms without the permission of developers.

*********************************************************************/

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <time.h>

#include "current_widget.h"
#include "ui_current_widget.h"
#include "dialog.h"


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Dialog d;
    d.show();
    return a.exec();
}



