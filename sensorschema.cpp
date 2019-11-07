#include "sensorschema.h"


//void SensorSchema::setColumn()
//{

//}

string SensorSchema::getSqlInsertCommand()
{
    MyUtitlity u;
   // "INSERT INTO Sensors(router_number, sensor_number, low_pass, high_pass) VALUES(`+routerNumber+`,`+sensorNumber+`,`+low_pass+`,`+high_pass+` )`"
    string temp = "INSERT INTO Sensor(tempureture, res, current, lowPassFilter, R0, RThereshould, operationTime, recoveryTime, operationTemp, recoveryTemp, tempuretureTh, gasType, pressureType, equation, RtoR0OrRtoDeltaR, tempActive, heaterActive, sensorActive) VALUES("+u.numberToString(tempureture)+","+u.numberToString(res)+","+u.numberToString(unsigned(current))
            +","+u.numberToString(unsigned(lowPassFilter))+","+u.numberToString(R0)+","+u.numberToString(RThereshould)+","+u.numberToString(operationTime)
            +","+u.numberToString(recoveryTime)+","+u.numberToString(operationTemp)+","+u.numberToString(recoveryTemp)+","+u.numberToString(tempuretureTh)
            +", \""+gasType+"\", \""+pressureType+"\","+u.numberToString(unsigned(equation))+","+u.numberToString(RtoR0OrRtoDeltaR)
            +","+u.numberToString(tempActive)+","+u.numberToString(heaterActive)+","+u.numberToString(sensorActive)+ ")";

//    cout<< static_cast<uint8_t>(current) <<", current " << u.numberToString(unsigned(current)) << endl;
//    cout<< static_cast<uint8_t>(lowPassFilter)<< ", lowPassFilter " << u.numberToString(unsigned(lowPassFilter)) << endl;
//    cout<< static_cast<uint8_t>(equation) << ", equation " << u.numberToString(unsigned(equation)) << endl;
    cout<< "getsqlCommand " << endl;
    cout<< temp << endl;
    return temp;
}
