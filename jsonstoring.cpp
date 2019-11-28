#include "jsonstoring.h"

JsonStoring::JsonStoring()
{

}
//struct BoardData {
//    uint8_t humidityIn = 0;
//    uint8_t humidityOut = 0;
//    uint8_t humidityArea = 0 ;
//    uint16_t pumpSpeed = 0 ;
//    uint8_t batteryCharge = 100;
//    bool chargingStatus = false;
//    bool flowErrorStatus = false;
//    bool electricalErrorStatus = false;
//    float presureSenesor = 0;
//    float tempuretureArea = 0;
//    float tempuretureBoard = 0;
//    bool fan1 = false;
//    bool fan2 = false;
//    string time ;
//};
void JsonStoring::storeBoardData(BoardData boardData)
{
     QJsonObject qJsonObject;
     qJsonObject.insert("humidityIn", boardData.humidityIn);
     qJsonObject.insert("humidityOut", boardData.humidityOut);
     qJsonObject.insert("humidityArea", boardData.humidityArea);
     qJsonObject.insert("pumpSpeed", boardData.pumpSpeed);
     qJsonObject.insert("batteryCharge", boardData.batteryCharge);
     qJsonObject.insert("chargingStatus", boardData.chargingStatus);
     qJsonObject.insert("flowErrorStatus", boardData.flowErrorStatus);
     qJsonObject.insert("electricalErrorStatus", boardData.electricalErrorStatus);
     qJsonObject.insert("presureSenesor", boardData.presureSenesor);
     qJsonObject.insert("tempuretureArea", boardData.tempuretureArea);
     qJsonObject.insert("tempuretureBoard", boardData.tempuretureBoard);
     qJsonObject.insert("fan1", boardData.fan1);
     qJsonObject.insert("fan2", boardData.fan2);

     QString data = jsonToString(qJsonObject);
     storeToFile(data, GeneralDataFile);
}

BoardData JsonStoring::getBoardData()
{
   QString jsonString = getFileString(GeneralDataFile);
   BoardData temp;
   if(jsonString == "") {
       cout<< "JsonStoring::getBoardData() does not exist"<<endl;
       return  temp;
   }
   QJsonDocument qJsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
   QJsonObject qJsonObject = qJsonDocument.object();
   temp.humidityIn = static_cast<uint8_t>(qJsonObject.value("humidityIn").toString().toUInt()) ;
   temp.humidityOut = static_cast<uint8_t>(qJsonObject.value("humidityOut").toString().toUInt()) ;
   temp.humidityArea = static_cast<uint8_t>(qJsonObject.value("humidityArea").toString().toUInt()) ;
   temp.pumpSpeed = static_cast<uint16_t>(qJsonObject.value("pumpSpeed").toString().toUInt()) ;
   temp.batteryCharge = static_cast<uint8_t>(qJsonObject.value("batteryCharge").toString().toUInt()) ;
   temp.chargingStatus = static_cast<uint8_t>(qJsonObject.value("chargingStatus").toString().toUInt()) ;
   temp.flowErrorStatus = static_cast<uint8_t>(qJsonObject.value("flowErrorStatus").toString().toUInt()) ;
   temp.electricalErrorStatus = static_cast<uint8_t>(qJsonObject.value("electricalErrorStatus").toString().toUInt()) ;
   temp.presureSenesor = qJsonObject.value("presureSenesor").toString().toFloat() ;
   temp.tempuretureArea = qJsonObject.value("tempuretureArea").toString().toFloat() ;
   temp.tempuretureBoard = qJsonObject.value("tempuretureBoard").toString().toFloat() ;
   temp.fan1 = static_cast<uint8_t>(qJsonObject.value("fan1").toString().toUInt()) ;
   temp.fan2 = static_cast<uint8_t>(qJsonObject.value("fan2").toString().toUInt()) ;
   return  temp;
}

QString JsonStoring::jsonToString(QJsonObject jsonObject)
{
    QJsonDocument doc(jsonObject);
    return  doc.toJson(QJsonDocument::Compact);
}

void JsonStoring::storeToFile(QString data, QString fileName)
{
    QFile file(fileName);
        if(file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
        {
            QTextStream textStream( &file );
            QStringList stringList;
            textStream << data;
            file.close();
        } else {
            cout<< " file " << fileName.data() << " could not open" << endl;
        }
}

QString JsonStoring::getFileString(QString fileName)
{
    QString temp = "";
    QFile file(fileName);
    if(!file.exists()) {
        return temp;
    }
    if( !file.open(QFile::ReadOnly | QFile::Text) ) {
        cout << fileName.data() << " File not exists "<<endl;
    } else {
        QTextStream in(&file);
        temp = in.readLine();
        file.close();
    }

    return temp;
}
