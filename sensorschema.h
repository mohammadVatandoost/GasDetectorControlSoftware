#ifndef SENSORSCHEMA_H
#define SENSORSCHEMA_H

#include "schema.h"

class SensorSchema : Schema
{
public:
    SensorSchema(string tableName) : Schema(tableName) {
        //addColumn()
    }
};

#endif // SENSORSCHEMA_H
