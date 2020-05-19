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

#ifndef DBTOOL_H
#define DBTOOL_H

#include <iostream>
#include <string>
#include "sqlite3.h"

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <set>
#include <map>

/**
 * @brief The Database management tool
 *
 * This object represents the running sqlite3 database
 * instance, which is run as part of a library.  This
 * is the class that loads the sqlite file and will
 * allow for the basic tools for manipulating that object.
 * The Database object is essentally a specialized engine
 * that implements the primary features of a SQL relational
 * database as a local instance.
 */

class DBTool {

private:

    /// Name of the database.
    std::string db_name;

    /// Location of the database in the file structure.
    std::string db_location;

    sqlite3 *curr_db;

public:

    // Constructor that if called will cause the program to exit
    // indicating that more information should be provided.
    DBTool();

    // Constructors for loading a database file in the current
    // working directory.
    DBTool(std::string name);
    DBTool(const char* name);

    // Constructors for loading a database file in a specified
    // directory location.
    DBTool(std::string location, std::string name);
    DBTool(const char* location, const char* name);

    // Destructor that will cause the database to be closed storing
    // the updated contents of the sqlite file.
    ~DBTool();

    // Used to manually open the file, and called by each of the
    // constructors.
    int open_db();

    // prints state of database
    void print(std::ostream &sout);

    // provides a state check to determine if database is available
    bool db_open() { return curr_db ? true : false; }

    // Returns a pointer to the current database, only
    // used when absolutely necessary!
    sqlite3* db_ref()  { return curr_db; }
};

#endif // DBTOOL_H

