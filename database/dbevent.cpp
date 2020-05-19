/*********************************************************************

Copyright (C) 2015 Jeffrey O. Pfaffmann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*********************************************************************/

#include "DBEvent.h"

DBEvent::DBEvent()
{

}

// Constructor for identying the dbtool and table name.
DBEvent::DBEvent(DBTool *db, string name) : DBTable (db, name)
{

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBEvent::DBEvent(DBEvent &obj) : DBTable (obj)
{

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

void DBEvent::operator=(DBEvent &obj) {
    // Store table name and reference to db.
    curr_db     = obj.curr_db;
    table_name  = obj.table_name;

    // Register the different sql calls for the
    // parent class.
    store_exist_sql();
    store_create_sql();
    store_drop_sql();
    store_size_sql();

    sql_add_row = "";

    // Load SQL specific to child class.
    store_add_row_sql();
    store_create_sql();

    // must build table sepparately so new
    // sql can be properly registered
    build_table();
}

DBEvent::~DBEvent() {

}

void DBEvent::store_add_row_sql() {

    sql_template =  "SELECT name ";
    sql_template += "FROM   sqlite_master ";
    sql_template += "WHERE";
    sql_template += "    type = \"table\"";
    sql_template += ";";

}

void DBEvent::store_create_sql() {

    sql_create =  "CREATE TABLE ";
    sql_create += table_name;
    sql_create += " ( ";
    //sql_create += "  id INT PRIMARY KEY NOT NULL AUTO_INCREMENT, ";
    sql_create += "  date TEXT NOT NULL, ";
    sql_create += "  time   TEXT NOT NULL, ";
    sql_create += "  hiveNumber  INT NOT NULL, ";
    sql_create += "  boardNumber  INT NOT NULL, ";
    sql_create += "  type   TEXT NOT NULL";
    sql_create += " );";
}



bool DBEvent::add_row(string date, string time, int hiveNumber, int boardNumber, string type) {
    int   retCode = 0;
    char *zErrMsg = 0;

    char  tempval[128];

    sql_add_row  = "INSERT INTO ";
    sql_add_row += table_name;
    sql_add_row += " (date, time, hiveNumber, boardNumber, type ) ";
    sql_add_row += "VALUES (";

    //    sprintf (tempval, "%d", id);
    //    sql_add_row += tempval;
    //    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += string(date);
    sql_add_row += "\", ";

    sql_add_row += "\"";
    sql_add_row += string(time);
    sql_add_row += "\", ";

    sprintf (tempval, "%d", hiveNumber);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sprintf (tempval, "%d", boardNumber);
    sql_add_row += tempval;
    sql_add_row += ", ";

    sql_add_row += "\"";
    sql_add_row += string(type);
    sql_add_row += "\"";

    sql_add_row += " );";


    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_add_row.c_str(),
                           cb_add_row,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

int cb_add_row(void  *data, int    argc, char **argv, char **azColName) {
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }

    int i;
    DBEvent *obj = (DBEvent *) data;

    std::cout << "------------------------------\n";
    std::cout << obj->get_name()
              << std::endl;

    for(i = 0; i < argc; i++){
        std::cout << azColName[i]
                     << " = "
                     <<  (argv[i] ? argv[i] : "NULL")
                      << std::endl;
    }

    return 0;

}

int cb_select_all(void  *data,
                  int    argc,
                  char **argv,
                  char **azColName)
{


    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }


    //int i;
    DBEvent *obj = (DBEvent *) data;

    //    std::cout << "------------------------------\n";
    //    std::cout << obj->get_name()
    //              << std::endl;

    //    for(i = 0; i < argc; i++){
    //        std::cout << azColName[i]
    //                     << " = "
    //                     <<  (argv[i] ? argv[i] : "NULL")
    //                      << std::endl;
    //    }

    if (obj->da !=nullptr){
        obj->da->construct_data(argc, argv, azColName);
    }

    return 0;
}

bool DBEvent::select_all() {

    int   retCode = 0;
    char *zErrMsg = 0;

    //sql_select_all  = "PRAGMA table_info(" + table_name + ");";
    sql_select_all = "SELECT * FROM ";
    sql_select_all += table_name;
    sql_select_all += ";";

    retCode = sqlite3_exec(curr_db->db_ref(),
                           sql_select_all.c_str(),
                           cb_select_all,
                           this,
                           &zErrMsg          );

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

int cb_select_where(void *data, int argc,
                    char **argv, char **azColName){
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    DBEvent *obj = (DBEvent *) data;
    if (obj->da !=nullptr){
        obj->da->construct_data(argc, argv, azColName);
    }

    return 0;

}

bool DBEvent::select_where(string startdate, string enddate, string hiveNumber){
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_where = "SELECT * FROM ";
    sql_select_where += table_name;
    sql_select_where += " WHERE date BETWEEN ";
    sql_select_where += "'"+ startdate + "' ";
    sql_select_where += "AND ";
    sql_select_where += "'"+ enddate + "' ";
    sql_select_where += "AND hiveNumber = ";
    sql_select_where += hiveNumber;
    sql_select_where += ";";

    retCode= sqlite3_exec(curr_db->db_ref(),
                          sql_select_where.c_str(),
                          cb_select_where,
                          this,
                          &zErrMsg);

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}

int cb_select_wheredtt(void *data, int argc,
                    char **argv, char **azColName){
    if(argc < 1) {
        std::cerr << "No data presented to callback "
                  << "argc = " << argc
                  << std::endl;
    }
    DBEvent *obj = (DBEvent *) data;
    if (obj->da !=nullptr){
        obj->da->construct_data(argc, argv, azColName);
    }

    return 0;

}

bool DBEvent::select_wheredtt(string date, string starttime,
                              string endtime, string hiveNumber, string type){
    int   retCode = 0;
    char *zErrMsg = 0;

    sql_select_wheredtt = "SELECT * FROM ";
    sql_select_wheredtt += table_name;
    sql_select_wheredtt += " WHERE date= ";
    sql_select_wheredtt += "'"+ date + "' ";
    sql_select_wheredtt += "AND time ";
    sql_select_wheredtt += "BETWEEN ";
    sql_select_wheredtt += "'"+ starttime + "' ";
    sql_select_wheredtt += "AND ";
    sql_select_wheredtt += "'"+ endtime + "' ";
    sql_select_wheredtt += "AND hiveNumber = ";
    sql_select_wheredtt += hiveNumber;
    sql_select_wheredtt += " AND type = ";
    sql_select_wheredtt += "'"+ type + "' ";
    sql_select_wheredtt += ";";

    retCode= sqlite3_exec(curr_db->db_ref(),
                          sql_select_wheredtt.c_str(),
                          cb_select_wheredtt,
                          this,
                          &zErrMsg);

    if( retCode != SQLITE_OK ){

        std::cerr << table_name
                  << " template ::"
                  << std::endl
                  << "SQL error: "
                  << zErrMsg;

        sqlite3_free(zErrMsg);
    }

    return retCode;
}
