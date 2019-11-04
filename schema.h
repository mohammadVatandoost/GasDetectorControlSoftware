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
    string sqlCommand;

    bool addColumn(string name, string type);
//    bool addColumn(string name, string type, bool notNull);
    bool addColumn(string name, string type, string defaultValue);

//    bool addColumnTest(string name, string type, int notNull);
//    bool addColumnTest(string name, string type, double defaultValue);

    bool checkIsNewColumnName(string name);
};

#endif // SCHEMA_H
