#include "schema.h"

bool Schema::checkIsNewColumnName(string name)
{
    for(int i=0; i<names.size(); i++) {
        if(names[i] == name) {
            return false;
        }
    }
    return true;
}

bool Schema::addColumn(string name, string type)
{
    if(checkIsNewColumnName(name)) {
        if(names.size() == 0) {
           sqlCommand = name + " " + type;
        } else {
            sqlCommand = sqlCommand + ", " + name + " " + type;
        }
        names.push_back(name);
        return true;
    }
    cout<< "Error: Schema addColumn: this " << name << "was added before please select new Name" << endl;
    return false;
}

bool Schema::addColumn(string name, string type, string defaultValue)
{
//    cout<< "addColumn with defaultValue"<<endl;
    if(checkIsNewColumnName(name)) {
        if(names.size() == 0) {
           sqlCommand = name + " " + type + " DEFAULT " + defaultValue;
        } else {
            sqlCommand = sqlCommand + ", " + name + " " + type + " DEFAULT " + defaultValue;
        }
        names.push_back(name);
        return true;
    }
    cout<< "Error: Schema addColumn: this " << name << "was added before please select new Name" << endl;
    return false;
}

//bool Schema::addColumnTest(string name, string type, int notNull)
//{
//    cout<< "addColumn with notNull"<<endl;
//}

//bool Schema::addColumnTest(string name, string type, double defaultValue)
//{
//    cout<< "addColumn with defaultValue"<<endl;
//}

//bool Schema::addColumn(string name, string type, bool notNull)
//{
//    cout<< "addColumn with notNull"<<endl;
//    if(checkIsNewColumnName(name)) {
//        string not_null = "NOT NULL";
//        if(notNull) { not_null = ""; }
//        if(names.size() == 0) {
//           sqlCommand = name + " " + type + " " + not_null;
//        } else {
//            sqlCommand = sqlCommand + ", " + name + " " + type + " " + not_null;
//        }
//        names.push_back(name);
//        return true;
//    }
//    cout<< "Error: Schema addColumn: this " << name << "was added before please select new Name" << endl;
//    return false;
//}
