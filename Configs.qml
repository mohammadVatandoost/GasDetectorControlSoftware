import QtQuick 2.0

Grid {
    id: root
    columns: 3
    spacing: 10
    property int sensorId: 0
    signal configSelected(int configId, string configName, string configValue)
    property var idMap: ({ config1: config1, config2: config2, config3: config3, config4: config4,
                            config5: config5, config6: config6, config7: config7, config8: config8, config9: config9})
    function findItemById(id) {
         return idMap[id];
    }

    function setConfigVaue(configId, configValue) {
       findItemById("config"+configId).setConfigValue(configValue);
    }

    function setSensorId(temp) {
        sensorId = temp;

        updateConfig();
    }

    function updateConfig() {
//        console.log("updateConfig");
//        console.log(sensorId);
        config1.setConfigValue(SensorsList.getFilterValue(sensorId));
        config2.setConfigValue(SensorsList.getR0Value(sensorId));
        config3.setConfigValue(SensorsList.getRtolValue(sensorId));
        config4.setConfigValue(BackEnd.getPumpValue());
        config5.setConfigValue(SensorsList.getOperationTempValue(sensorId));
        config6.setConfigValue(SensorsList.getTRtolValue(sensorId));
        config7.setConfigValue(SensorsList.getRecTimeValue(sensorId));
        config8.setConfigValue(SensorsList.getRecTempValue(sensorId));
        config9.setConfigValue(SensorsList.getOPTimeValue(sensorId));
    }

    Component.onCompleted: {
        updateConfig();
    }

    ConfigItem {
     id: config1
     Component.onCompleted: {
       setConfigId(1);
       setConfigName("Filter");
//       setConfigValue("10");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config2
     Component.onCompleted: {
       setConfigId(2);
       setConfigName("R0");
//       setConfigValue("19.84");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config3
     Component.onCompleted: {
       setConfigId(3);
       setConfigName("Rtol");
//       setConfigValue("3");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config4
     Component.onCompleted: {
       setConfigId(4);
       setConfigName("PUMP");
//       setConfigValue("6");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config5
     Component.onCompleted: {
       setConfigId(5);
       setConfigName("OP Temp");
//       setConfigValue("4");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config6
     Component.onCompleted: {
       setConfigId(6);
       setConfigName("TRtol");
//       setConfigValue("0");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config7
     Component.onCompleted: {
       setConfigId(7);
       setConfigName("Rec Time");
//       setConfigValue("0");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config8
     Component.onCompleted: {
       setConfigId(8);
       setConfigName("Rec Temp");
//       setConfigValue("0");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
        id: config9
     Component.onCompleted: {
       setConfigId(9);
       setConfigName("OP Time");
//       setConfigValue("4");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    Timer {
            interval: 1500; running: true; repeat: true
            onTriggered: {
                config2.setConfigValue(SensorsList.getR0Value(sensorId));
            }
     }
}

