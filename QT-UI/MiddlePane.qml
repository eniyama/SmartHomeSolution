import QtQuick
import QtQuick.Layouts
//import QtQuick
import QtQuick.Controls

import "."    // <-- THIS fixes MiddlePaneWidget visibility


Item {
    id: middleItem
    width: 152
    height: parent.height
    anchors.left: leftItem.right
    anchors.leftMargin: 22

    ColumnLayout {
        anchors.fill: parent
        spacing: 16

        MiddlePaneWidget {
            label: qsTr('Temperature')
            units: qsTr('°C')
            value: mqttManager.temperature

        }
       /* MiddlePaneWidget {
            label: qsTr("Distance")
            units: qsTr("cm")
            value: Mqtt.distance
        }*/

        MiddlePaneWidget {
            label: qsTr('Humidity')
            units: qsTr('%')
            value: mqttManager.humidity
        }

        MiddlePaneWidget {
            label: qsTr('Heating')
            units: qsTr('°C')
            value: heating
        }

        MiddlePaneWidget {
            label: qsTr('Water')
            units: qsTr('kpa')
            value: water
            alignUnitsRight: false
        }
    }
}
