import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    width: parent ? parent.width : 200
    height: 50
    radius: 12
    color: "#ECF0F1CC"  // background of switch component
    border.width: 1
    border.color: "#BDC3C7"

    property alias label: switchLabel.text
    property alias checked: toggleSwitch.checked
    property color labelColor: "black"

    // Expose a reusable switch component for external use
    property Component exposedSwitch: Component {
        Switch {
            id: exposedStyledSwitch
            checked: root.checked
            Layout.alignment: Qt.AlignVCenter
            palette.highlight: "#5CE1E6"
            palette.button: "#48709F"

            // Keep root.checked synced
            onCheckedChanged: root.checked = checked
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 16

        Text {
            id: switchLabel
            text: "Switch"
            font.pixelSize: 14
            font.bold: true
            color: labelColor
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }

        // Use your existing Switch with custom colors
        Switch {
            id: toggleSwitch
            checked: false
            Layout.alignment: Qt.AlignVCenter

            palette.highlight: "#5CE1E6"
            palette.button: "#48709F"
        }
    }
}
