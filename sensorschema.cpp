#include "sensorschema.h"


//void SensorSchema::setColumn()
//{

//}

string SensorSchema::getSqlInsertCommand()
{
    MyUtitlity u;
    string temp = "INSERT INTO Sensor(TRtol, res, current, lowPassFilter, R0, Rtol, operationTime, recoveryTime, operationTemp, recoveryTemp, tempuretureTh, gasType, pressureType, equation, equationA, equationB, equationC, equationD, equationE, RtoR0OrRtoDeltaR, tempActive, heaterActive, sensorActive) VALUES("+u.numberToString(TRtol)+","+u.numberToString(res)+","+u.numberToString(unsigned(current))
            +","+u.numberToString(unsigned(lowPassFilter))+","+u.numberToString(R0)+","+u.numberToString(Rtol)+","+u.numberToString(operationTime)
            +","+u.numberToString(recoveryTime)+","+u.numberToString(operationTemp)+","+u.numberToString(recoveryTemp)+","+u.numberToString(tempuretureTh)
            +", \""+gasType+"\", \""+pressureType+"\","+u.numberToString(unsigned(equation))+","+u.numberToString(equationA)+","+u.numberToString(equationB)
            +","+u.numberToString(equationC)+","+u.numberToString(equationD)+","+u.numberToString(equationE)+","+u.numberToString(RtoR0OrRtoDeltaR)
            +","+u.numberToString(tempActive)+","+u.numberToString(heaterActive)+","+u.numberToString(sensorActive)+ ")";
    return temp;
}

string SensorSchema::getSqlUpdateCommand(uint8_t sensorId)
{
    sensorId = sensorId + 1;
    MyUtitlity u;
    //`UPDATE EEWConfig SET accTreshold = "`+accTreshold+`", highPass = "`+highPass+`", lowPass = "`+lowPass+`", longPoint = "`+longPoint+`", shortPoint = "`+shortPoint+`", staLtaTreshold = "`+staLtaTreshold+`", winLength = "`+winLength+`", a1 = "`+a1+`", a2 ="`+a2+`", a3="`+a3+`", a4="`+a4+`" WHERE id = 1` ;
    string temp = "UPDATE Sensor SET TRtol="+u.numberToString(TRtol)+", res="+u.numberToString(res)+
            ", current="+u.numberToString(unsigned(current))+", lowPassFilter="+u.numberToString(unsigned(lowPassFilter))+
            ", R0="+u.numberToString(R0)+", Rtol="+u.numberToString(Rtol)+", operationTime="+u.numberToString(operationTime)+
            ", recoveryTime="+u.numberToString(recoveryTime)+", operationTemp="+u.numberToString(operationTemp)+
            ", recoveryTemp="+u.numberToString(recoveryTemp)+", tempuretureTh="+u.numberToString(tempuretureTh)+
            ", gasType=\""+gasType+"\", pressureType=\""+pressureType+"\", equation="+u.numberToString(unsigned(equation))+
            ", equationA="+u.numberToString(equationA)+", equationB="+u.numberToString(equationB)+
            ", equationC="+u.numberToString(equationC)+", equationD="+u.numberToString(equationD)+
            ", equationE="+u.numberToString(equationE)+
            ", RtoR0OrRtoDeltaR="+u.numberToString(RtoR0OrRtoDeltaR)+", tempActive="+u.numberToString(tempActive)+
            ", heaterActive="+u.numberToString(heaterActive)+", sensorActive="+u.numberToString(sensorActive)+" WHERE id = "+u.numberToString(unsigned(sensorId));
//    cout << "getSqlUpdateCommand :"<< temp;
    return temp;
}

string SensorSchema::getSqlFindById(uint8_t sensorId)
{
    sensorId = sensorId + 1;
   MyUtitlity u;
   string temp = "SELECT * FROM Sensor WHERE id="+u.numberToString(unsigned(sensorId));
//   cout << "getSqlFindById :"<< temp;
   return temp;
}

void SensorSchema::setSensorInfo(Sensor temp)
{
    RtoR0OrRtoDeltaR = temp.RtoR0OrRtoDeltaR;
    tempActive = temp.tempActive;
    heaterActive = temp.heaterActive;
    sensorActive = temp.sensorActive;
//    cout << pressureType << ", pressureType :"<< temp.pressureType.toStdString();
    pressureType = temp.pressureType.toUtf8().toStdString();
    equation = temp.equation;
    equationA = temp.equationA;
    equationB = temp.equationB;
    equationC = temp.equationC;
    equationD = temp.equationD;
    equationE = temp.equationE;

    recoveryTime = temp.recoveryTime;
    operationTemp = temp.operationTemp;
    current = temp.current;
    recoveryTemp = temp.recoveryTemp;
    tempuretureTh = temp.tempuretureTh;
    gasType = temp.gasType.toStdString();

    TRtol = temp.TRtol;
    res = temp.res;
    current = temp.current;
    R0 = temp.R0;
    Rtol = temp.Rtol;
    operationTime = temp.operationTime;
}
