QT += quick
QT += serialport
QT += sql
QT += qml
QT += charts
QT += opengl
QT += quickcontrols2
CONFIG += c++11
CONFIG += disable-desktop
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

LIBS += -ldl

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    backend.cpp \
    csv.cpp \
    sensorslist.cpp \
    sensormodel.cpp \
    sqlite3.c \
    database.cpp \
    schema.cpp \
    sensorschema.cpp \
    jsonstoring.cpp \
    serialport.cpp \
    brookschannel.cpp \
    brooks0254.cpp \
    channelslist.cpp \
    brookschannelmodel.cpp

#LIBS += /usr/lib/libgtest.a

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    backend.h \
    csv.h \
    sensorslist.h \
    sensor.h \
    sensormodel.h \
    sqlite3.h \
    sqlite3ext.h \
    database.h \
    schema.h \
    sensorschema.h \
    jsonstoring.h \
    packet.h \
    myutitlity.h \
    serialport.h \
    brookschannel.h \
    brooks0254.h \
    channelslist.h \
    brookschannelmodel.h

DISTFILES += \
    images/greenTemp.png \
    images/oilCompany.png


