#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQuickWindow>
#include <QApplication>
#include "sensormodel.h"
#include "sensorslist.h"
#include "backend.h"
#include "database.h"
#include <cstdio>


int main(int argc, char *argv[])
{
//    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    // Load virtualkeyboard input context plugin
    qputenv("QT_IM_MODULE", QByteArray("freevirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    freopen("output.txt","w",stdout);
//    QGuiApplication app(argc, argv);
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    qmlRegisterType<SensorModel>("SensorModel", 1, 0, "SensorModel");
    qmlRegisterUncreatableType<SensorsList>("SensorsList",1,0,"SensorsList",
                                       QStringLiteral("SensorsList should not be created in QML"));
    DataBase db{"dataBase"};
    SensorsList sensorsList;
    sensorsList.setDataBase(&db);
    Backend backEnd;
    backEnd.setDataBase(&db);
    backEnd.setSensorsList(&sensorsList);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("SensorsList"), &sensorsList);
    engine.rootContext()->setContextProperty(QStringLiteral("BackEnd"), &backEnd);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    // for connecting qml slot to c++ signal
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

//    window->showFullScreen();
    // connect our QML signal to our C++ slot
//    QObject::connect(&backEnd, SIGNAL(notifyInfoDataChanged()),
//                            window, SLOT(refreshData()));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
