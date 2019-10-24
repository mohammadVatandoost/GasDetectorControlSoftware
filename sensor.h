#ifndef SENSOR_H
#define SENSOR_H
#include <iostream>

using namespace std;

enum FormulType{ first, second, third };
enum ValueType{ PPM, PDB };
enum GasKind{ NO, CO, SO2, O2, BTEX, VOC};

struct Sensor {
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
    GasKind gasType = GasKind::NO;
    ValueType type = ValueType::PPM;
    bool RtoR0OrRtoDeltaR = true;
    FormulType equation = FormulType::first;
};


#endif // SENSOR_H
