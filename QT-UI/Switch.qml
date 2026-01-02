import QtQuick

Rectangle {
    id: root
    implicitHeight: 20
    implicitWidth: 40
    radius: height / 2
    color: checked ? "#48709F" : "#3C608B"

    Behavior on color { ColorAnimation { duration: 200 } }

    // switch state
    property bool checked: false
    signal toggled(bool checked)

    Rectangle {
        id: indicator
        color: checked ? "#ffffff" : textColor
        width: root.height - 4
        height: width
        radius: height / 2
        x: checked ? (root.width - width - 2) : 2
        anchors.verticalCenter: parent.verticalCenter

        Behavior on x { NumberAnimation { duration: 200 } }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            checked = !checked
            root.toggled(checked)

            var state = checked ? "ON" : "OFF"

            if (typeof mqttManager !== "undefined" && mqttManager) {
                console.log("Sending Light:", state)
                mqttManager.publishSwitch("light", state)
            } else {
                console.log("mqttManager not set")
            }
        }
    }
}
