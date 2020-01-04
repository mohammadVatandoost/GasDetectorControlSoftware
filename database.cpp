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
    cout<<endl<<"update : " << sql_command << endl;
    exit = sqlite3_exec(DB, sql_command.c_str(), callback, 0, &zErrMsg);

      if( exit != SQLITE_OK ){
         cerr << "SQL error: " << zErrMsg << endl;
         sqlite3_free(zErrMsg);
         return false;
      } else {
         cout <<  " table update successfully" << endl;
         cout <<  zErrMsg << endl;
         return true;
      }
}

bool DataBase::findById(string sql_command, Sensor *temp)
{
    int exit = 0;
    char q[999];
    sqlite3_stmt* stmt;
    int row = 0;
    int bytes;
    const unsigned char* text;

    if(!isOpen) { cout<<"findById connection is not open";  return false;}

    sqlite3_prepare(DB, sql_command.c_str(), sizeof q, &stmt, NULL);

    bool done = false;
    bool successfullyFinded = false;
        while (!done) {
            printf("In select while\n");
            switch (sqlite3_step (stmt)) {
              case SQLITE_ROW:
//                cout<< "column counter :" << sqlite3_column_count(stmt) << endl;
//                cout<< "id :" << sqlite3_column_double(stmt, 0) << endl;
//                cout<< "tempureture :" << sqlite3_column_double(stmt, 1) << endl;
//                cout<< "res :" << sqlite3_column_double(stmt, 2) << endl;
//                cout<< "current :" << sqlite3_column_int(stmt, 3) << endl;
//                cout<< "lowPassFilter :" << sqlite3_column_int(stmt, 4) << endl;
//                cout<< "R0 :" << sqlite3_column_int(stmt, 5) << endl;
//                cout<< "RThereshould :" << sqlite3_column_int(stmt, 6) << endl;
//                cout<< "operationTime :" << sqlite3_column_int(stmt, 7) << endl;
//                cout<< "recoveryTime :" << sqlite3_column_int(stmt, 8) << endl;
//                cout<< "operationTemp :" << sqlite3_column_double(stmt, 9) << endl;
//                cout<< "recoveryTemp :" << sqlite3_column_double(stmt, 10) << endl;
//                cout<< "tempuretureTh :" << sqlite3_column_double(stmt, 11) << endl;
//                cout<< "gasType :" << sqlite3_column_text(stmt, 12) << endl;
//                cout<< "pressureType :" << sqlite3_column_text(stmt, 13) << endl;
//                cout<< "equation :" << sqlite3_column_int(stmt, 14) << endl;
//                cout<< "RtoR0OrRtoDeltaR :" << sqlite3_column_int(stmt, 15) << endl;
//                cout<< "tempActive :" << sqlite3_column_int(stmt, 16) << endl;
//                cout<< "heaterActive :" << sqlite3_column_int(stmt, 17) << endl;
//                cout<< "sensorActive :" << sqlite3_column_int(stmt, 18) << endl;
                temp->TRtol = static_cast<uint16_t>(sqlite3_column_double(stmt, 1)) ;
                temp->res = static_cast<float>(sqlite3_column_double(stmt, 2)) ;
                temp->current = static_cast<uint8_t>(sqlite3_column_int(stmt, 3)) ;
                temp->lowPassFilter = static_cast<uint8_t>(sqlite3_column_int(stmt, 4)) ;
                temp->R0 = static_cast<uint16_t>(sqlite3_column_int(stmt, 5)) ;
                temp->Rtol = static_cast<uint16_t>(sqlite3_column_int(stmt, 6)) ;
                temp->operationTime = static_cast<uint16_t>(sqlite3_column_int(stmt, 7)) ;
                temp->recoveryTime = static_cast<uint16_t>(sqlite3_column_int(stmt, 8)) ;
                temp->operationTemp = static_cast<float>(sqlite3_column_double(stmt, 9)) ;
                temp->recoveryTemp = static_cast<float>(sqlite3_column_double(stmt, 10)) ;
                temp->tempuretureTh = static_cast<float>(sqlite3_column_double(stmt, 11)) ;
                temp->gasType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12))  ;
                temp->pressureType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 13)) ;

                temp->equation = static_cast<uint8_t>(sqlite3_column_int(stmt, 14)) ;
                temp->equationA = static_cast<float>(sqlite3_column_double(stmt, 15)) ;
                temp->equationB = static_cast<float>(sqlite3_column_double(stmt, 16)) ;
                temp->equationC = static_cast<float>(sqlite3_column_double(stmt, 17)) ;
                temp->equationD = static_cast<float>(sqlite3_column_double(stmt, 18)) ;
                temp->equationE = static_cast<float>(sqlite3_column_double(stmt, 19)) ;

                temp->RtoR0OrRtoDeltaR = static_cast<uint8_t>(sqlite3_column_int(stmt, 20)) ;
//                temp->tempActive = static_cast<uint8_t>(sqlite3_column_int(stmt, 21)) ;
//                temp->heaterActive = static_cast<uint8_t>(sqlite3_column_int(stmt, 22)) ;
//                temp->sensorActive = static_cast<uint8_t>(sqlite3_column_int(stmt, 23)) ;
                successfullyFinded = true;
//                bytes = sqlite3_column_bytes(stmt, 0);
//                text  = sqlite3_column_text(stmt, 1);
//                printf ("count %d: %s (%d bytes)\n", row, text, bytes);
                row++;
                break;

              case SQLITE_DONE:
                 done = true;
                 break;

              default:
                fprintf(stderr, "Failed.\n");
                return false;
            }
        }

        sqlite3_finalize(stmt);

        return successfullyFinded;
}
