#include "sensorschema.h"


//void SensorSchema::setColumn()
//{

//}

string SensorSchema::getSqlInsertCommand()
{
    MyUtitlity u;
    string temp = "INSERT INTO Sensor(tempureture, res, current, lowPassFilter, R0, RThereshould, operationTime, recoveryTime, operationTemp, recoveryTemp, tempuretureTh, gasType, pressureType, equation, RtoR0OrRtoDeltaR, tempActive, heaterActive, sensorActive) VALUES("+u.numberToString(tempureture)+","+u.numberToString(res)+","+u.numberToString(unsigned(current))
            +","+u.numberToString(unsigned(lowPassFilter))+","+u.numberToString(R0)+","+u.numberToString(RThereshould)+","+u.numberToString(operationTime)
            +","+u.numberToString(recoveryTime)+","+u.numberToString(operationTemp)+","+u.numberToString(recoveryTemp)+","+u.numberToString(tempuretureTh)
            +", \""+gasType+"\", \""+pressureType+"\","+u.numberToString(unsigned(equation))+","+u.numberToString(RtoR0OrRtoDeltaR)
            +","+u.numberToString(tempActive)+","+u.numberToString(heaterActive)+","+u.numberToString(sensorActive)+ ")";
    return temp;
}

string SensorSchema::getSqlUpdateCommand(uint8_t sensorId)
{
    MyUtitlity u;
    //`UPDATE EEWConfig SET accTreshold = "`+accTreshold+`", highPass = "`+highPass+`", lowPass = "`+lowPass+`", longPoint = "`+longPoint+`", shortPoint = "`+shortPoint+`", staLtaTreshold = "`+staLtaTreshold+`", winLength = "`+winLength+`", a1 = "`+a1+`", a2 ="`+a2+`", a3="`+a3+`", a4="`+a4+`" WHERE id = 1` ;
    string temp = "UPDATE Sensor SET tempureture="+u.numberToString(tempureture)+", res="+u.numberToString(res)+
            ", current="+u.numberToString(unsigned(current))+", lowPassFilter="+u.numberToString(unsigned(lowPassFilter))+
            ", R0="+u.numberToString(R0)+", RThereshould="+u.numberToString(RThereshould)+", operationTime="+u.numberToString(operationTime)+
            ", recoveryTime="+u.numberToString(recoveryTime)+", operationTemp="+u.numberToString(operationTemp)+
            ", recoveryTemp="+u.numberToString(recoveryTemp)+", tempuretureTh="+u.numberToString(tempuretureTh)+
            ", gasType=\""+gasType+"\", pressureType=\""+pressureType+"\", equation="+u.numberToString(unsigned(equation))+
            ", RtoR0OrRtoDeltaR="+u.numberToString(RtoR0OrRtoDeltaR)+", tempActive="+u.numberToString(tempActive)+
            ", heaterActive="+u.numberToString(heaterActive)+", sensorActive="+u.numberToString(sensorActive)+" WHERE id = "+u.numberToString(unsigned(sensorId));
    cout << "getSqlUpdateCommand :"<< temp;
    return temp;
}
