#ifndef PACKET_H
#define PACKET_H

#include <iostream>

#define HeaterNotActive 40010

#define SensorDataPacketCodeRx 1
#define BoardDataPacketCodeRx 2
#define SensorSetPointPacketCodeTx 3
#define PumpSpeedPacketCodeTx 4

using namespace std;

#pragma pack(push, 1)

struct BoardData {
    uint8_t humidityIn = 0;
    uint8_t humidityOut = 0;
    uint8_t humidityArea = 0 ;
    uint16_t pumpSpeed = 0 ;
    uint8_t batteryCharge = 100;
    bool chargingStatus = false;
    bool flowErrorStatus = false;
    bool electricalErrorStatus = false;
    float presureSenesor = 0;
    float tempuretureArea = 0;
    float tempuretureBoard = 0;
    bool fan1 = false;
    bool fan2 = false;
    string time ;
};

struct SensorPacketTx {
    uint8_t packetCode = SensorSetPointPacketCodeTx;
    uint8_t sensorId;
    uint16_t tempSetPoint;
};

struct SensorPacketRx {
    uint8_t sensorId;
    uint16_t temp;
    uint8_t current;
    uint32_t res;
};

struct BoardPacketTx {
    uint8_t packetCode = PumpSpeedPacketCodeTx;
    uint8_t pumpSpeed;
};

struct BoardPacketRx {
    uint8_t humidityIn;
    uint8_t humidityOut;
    uint8_t humidityArea;
    uint8_t pumpSpeed;
    uint16_t tempArea;
    uint16_t tempBoard;
    uint8_t flowErrorStatus; // boolean
    uint8_t electricalErrorStatus; // boolean
    uint8_t powerCharge;
    uint8_t batteryCharge;
    uint16_t pressureSensor;
    uint8_t fan1; // boolean
    uint8_t fan2; // boolean
};


#endif // PACKET_H
