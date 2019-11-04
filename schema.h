#ifndef SCHEMA_H
#define SCHEMA_H

#include <iostream>
#include <vector>

using namespace std;

class Schema
{
public:
    string tableName;
    Schema(string tableName) : tableName(tableName) {}
    vector<string> names;
    vector<string> types;

    bool addColumn(string name, string type);

private:
    bool checkIsNewColumnName(string name);
};

#endif // SCHEMA_H
