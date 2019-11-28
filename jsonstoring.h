#ifndef JSONSTORING_H
#define JSONSTORING_H

#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include "packet.h"

#define GeneralDataFile "GenralData.txt"




using namespace std;

class JsonStoring
{
public:
    JsonStoring();
    void storeBoardData(BoardData boardData);
    BoardData getBoardData();
    QString jsonToString(QJsonObject jsonObject);
    void storeToFile(QString data, QString fileName);
    QString getFileString(QString fileName);
};

#endif // JSONSTORING_H
