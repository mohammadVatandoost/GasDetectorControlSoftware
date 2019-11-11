#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"
#include "schema.h"
#include "sensor.h"

using namespace std;

class DataBase
{
public:
    string dbName;
    sqlite3* DB;
    bool isOpen = false;

    DataBase(string dbName) : dbName(dbName)  {}
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    bool openConnection();
    bool createTable(Schema tableSchema);
    bool insert(string sql_command);
    bool update(string sql_command);
    Sensor findById(string sql_command);
};

#endif // DATABASE_H
