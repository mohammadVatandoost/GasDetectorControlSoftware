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
      names.push_back(name);
      types.push_back(type);
      return true;
    }
    cout<< "Error: Schema addColumn: this " << name << "was added before please select new Name" << endl;
    return false;
}
