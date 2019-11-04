#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class DataBase
{
public:
    DataBase(string dbName);
    string dbName;
};

#endif // DATABASE_H
