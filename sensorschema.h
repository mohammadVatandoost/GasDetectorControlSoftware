#ifndef SENSORSCHEMA_H
#define SENSORSCHEMA_H

#include "schema.h"
#include "myutitlity.h"
#include "sensor.h"

// it must mention public, default is private
class SensorSchema : public Schema
{
public:
    string sqlInsert = "";
    string columnNames = "";
    string columnValues = "";

    float tempureture = 0;
    float res = 0;
    uint8_t current = 0;
    uint8_t lowPassFilter = 1;
    uint16_t R0 = 0; // for alghoritm
    uint16_t RThereshould = 0 ;
    uint16_t operationTime = 1 ;
    uint16_t recoveryTime = 1 ;
    float operationTemp = 0;
    float recoveryTemp = 0;
    float tempuretureTh = 0 ; // for T1 in page 1
    string gasType = "NO";
    string pressureType = "PPM";
    uint8_t equation = 0;
    float equationA = 1;
    float equationB = 2;
    float equationC = 2;
    float equationD = 2;
    float equationE = 2;
    bool RtoR0OrRtoDeltaR = true;
    bool tempActive = false;
    bool heaterActive = false;
    bool sensorActive = false;

    // TEXT, NUMERIC, INTEGER, REAL, BLOBi
    SensorSchema() : Schema("Sensor") {
        addColumn("tempureture", "REAL", static_cast<string>("0") );
        addColumn("res", "REAL", static_cast<string>("0") );
        addColumn("current", "INTEGER", static_cast<string>("0") );
        addColumn("lowPassFilter", "INTEGER", static_cast<string>("1") );
        addColumn("R0", "INTEGER", static_cast<string>("0") );
        addColumn("RThereshould", "INTEGER", static_cast<string>("0") );
        addColumn("operationTime", "INTEGER", static_cast<string>("1") );
        addColumn("recoveryTime", "INTEGER", static_cast<string>("1") );
        addColumn("operationTemp", "REAL", static_cast<string>("0") );
        addColumn("recoveryTemp", "REAL", static_cast<string>("0") );
        addColumn("tempuretureTh", "REAL", static_cast<string>("0") );
        addColumn("gasType", "TEXT", static_cast<string>("NO") );
        addColumn("pressureType", "TEXT", static_cast<string>("PPM") );
        addColumn("equation", "INTEGER", static_cast<string>("1") );
        addColumn("equationA", "REAL", static_cast<string>("1") );
        addColumn("equationB", "REAL", static_cast<string>("1") );
        addColumn("equationC", "REAL", static_cast<string>("1") );
        addColumn("equationD", "REAL", static_cast<string>("1") );
        addColumn("equationE", "REAL", static_cast<string>("1") );
        addColumn("RtoR0OrRtoDeltaR", "INTEGER", static_cast<string>("0") ); // boolean zero and one
        addColumn("tempActive", "INTEGER", static_cast<string>("0") ); // boolean zero and one
        addColumn("heaterActive", "INTEGER", static_cast<string>("0") ); // boolean zero and one
        addColumn("sensorActive", "INTEGER", static_cast<string>("0") ); // boolean zero and one

        cout << "Schema command :" << sqlCommand <<endl;
    }

    string getSqlInsertCommand();
    string getSqlUpdateCommand(uint8_t sensorId);
    string getSqlFindById(uint8_t sensorId);
};

#endif // SENSORSCHEMA_H
