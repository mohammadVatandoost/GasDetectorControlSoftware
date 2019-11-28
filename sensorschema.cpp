#include "sensorschema.h"


//void SensorSchema::setColumn()
//{

//}

string SensorSchema::getSqlInsertCommand()
{
    MyUtitlity u;
    string temp = "INSERT INTO Sensor(tempureture, res, current, lowPassFilter, R0, RThereshould, operationTime, recoveryTime, operationTemp, recoveryTemp, tempuretureTh, gasType, pressureType, equation, equationA, equationB, equationC, equationD, equationE, RtoR0OrRtoDeltaR, tempActive, heaterActive, sensorActive) VALUES("+u.numberToString(tempureture)+","+u.numberToString(res)+","+u.numberToString(unsigned(current))
            +","+u.numberToString(unsigned(lowPassFilter))+","+u.numberToString(R0)+","+u.numberToString(RThereshould)+","+u.numberToString(operationTime)
            +","+u.numberToString(recoveryTime)+","+u.numberToString(operationTemp)+","+u.numberToString(recoveryTemp)+","+u.numberToString(tempuretureTh)
            +", \""+gasType+"\", \""+pressureType+"\","+u.numberToString(unsigned(equation))+","+u.numberToString(equationA)+","+u.numberToString(equationB)
            +","+u.numberToString(equationC)+","+u.numberToString(equationD)+","+u.numberToString(equationE)+","+u.numberToString(RtoR0OrRtoDeltaR)
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
            ", RtoR0OrRtoDeltaR="+u.numberToString(equationA)+", RtoR0OrRtoDeltaR="+u.numberToString(equationB)+
            ", RtoR0OrRtoDeltaR="+u.numberToString(equationC)+", RtoR0OrRtoDeltaR="+u.numberToString(equationD)+
            ", RtoR0OrRtoDeltaR="+u.numberToString(equationE)+
            ", RtoR0OrRtoDeltaR="+u.numberToString(RtoR0OrRtoDeltaR)+", tempActive="+u.numberToString(tempActive)+
            ", heaterActive="+u.numberToString(heaterActive)+", sensorActive="+u.numberToString(sensorActive)+" WHERE id = "+u.numberToString(unsigned(sensorId));
//    cout << "getSqlUpdateCommand :"<< temp;
    return temp;
}

string SensorSchema::getSqlFindById(uint8_t sensorId)
{
   MyUtitlity u;
   string temp = "SELECT * FROM Sensor WHERE id="+u.numberToString(unsigned(sensorId));
//   cout << "getSqlFindById :"<< temp;
   return temp;
}
