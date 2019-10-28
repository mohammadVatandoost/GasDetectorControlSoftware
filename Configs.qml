import QtQuick 2.0

Grid {
    id: root
    columns: 3
    spacing: 10
    signal configSelected(int configId, string configName, string configValue)

    ConfigItem {
     Component.onCompleted: {
       setConfigId(1);
       setConfigName("Filter");
       setConfigValue("10");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(2);
       setConfigName("R0");
       setConfigValue("19.84");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(3);
       setConfigName("R tol");
       setConfigValue("3");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(4);
       setConfigName("PUMP");
       setConfigValue("6");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(5);
       setConfigName("Temp");
       setConfigValue("4");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(6);
       setConfigName("Name");
       setConfigValue("0");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(7);
       setConfigName("Rec Time");
       setConfigValue("0");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(8);
       setConfigName("Rec Temp");
       setConfigValue("0");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }

    ConfigItem {
     Component.onCompleted: {
       setConfigId(9);
       setConfigName("OP Time");
       setConfigValue("4");
     }

     onConfigSelected: {root.configSelected(configId, configName, configValue);console.log(configId + ", " + configName + ", "+ configValue);}
    }
}

