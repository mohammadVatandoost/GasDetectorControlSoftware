#include "database.h"


int DataBase::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++) {
        cout<<azColName[i] <<", "<< argv[i] ? argv[i] : "NULL" ;
        cout<<endl;
    }
    return 0;
}

bool DataBase::openConnection()
{
  int exit = 0;
  string str = dbName+".db";
  const char *cstr = str.c_str(); // convert string to char *
  exit = sqlite3_open( cstr, &DB);

  if (exit != SQLITE_OK) {
          cerr << "Error Open connection" << endl;
  } else {
      isOpen = true;
      cout << dbName << " connection opened"<< endl;
      return true;
  }
}

bool DataBase::createTable(Schema tableSchema)
{
    int exit = 0;

    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    string sql = "CREATE TABLE IF NOT EXISTS "+ tableSchema.tableName +" (id INTEGER PRIMARY KEY AUTOINCREMENT,"+tableSchema.sqlCommand+")";
//    sql= "CREATE TABLE IF NOT EXISTS Sensors (id INTEGER PRIMARY KEY AUTOINCREMENT, router_number INTEGER NOT NULL, sensor_number INTEGER NOT NULL, low_pass TEXT NOT NULL, high_pass TEXT NOT NULL, saving_local INTEGER DEFAULT 0, saving_web INTEGER DEFAULT 0, onRoof INTEGER DEFAULT 0, onGround INTEGER DEFAULT 0  )";
    cout<<endl<<"createTable : " << sql << endl;
    exit = sqlite3_exec(DB, sql.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "SQL error: " << zErrMsg << endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout << tableSchema.tableName << " table created successfully" << endl;
         return true;
      }
}

bool DataBase::insert(string sql_command)
{
    int exit = 0;

    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    cout<<endl<<"insert : " << sql_command << endl;
    exit = sqlite3_exec(DB, sql_command.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "SQL error: " << zErrMsg << endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout <<  " table inserted successfully" << endl;
         return true;
      }
}

bool DataBase::update(string sql_command)
{
    int exit = 0;

    if(!isOpen) {return false;}

    char *zErrMsg = 0;
    cout<<endl<<"insert : " << sql_command << endl;
    exit = sqlite3_exec(DB, sql_command.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "SQL error: " << zErrMsg << endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout <<  " table update successfully" << endl;
         return true;
      }
}
