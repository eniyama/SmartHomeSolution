import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: laundryWindow
    width: 400
    height: 600
    visible: false
    title: "Laundry Room"

    Rectangle {
        anchors.fill: parent
        color: "#145A32"     // dark leafy green

        Rectangle {
            id: cardPanel
            width: parent.width * 0.82
            height: parent.height * 0.78
            radius: 24
            anchors.centerIn: parent

            color: "#E9F7EFCC"      // soft mint glass
            border.width: 1
            border.color: "#A9DFBF"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                Text {
                    text: "Laundry Appliances"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#0E3E26"
                    Layout.alignment: Qt.AlignHCenter
                }

                Rectangle { height: 1; color: "#A9DFBF"; Layout.fillWidth: true }

                RightPaneLightSwitchComponent {
                    label: "Washing Machine"
                    labelColor: "black"
                    Layout.fillWidth: true


                }

                RightPaneLightSwitchComponent {
                    label: "Dryer"
                    labelColor: "black"
                    Layout.fillWidth: true


                }

                RightPaneLightSwitchComponent {
                    label: "Water Heater"
                    labelColor: "black"
                    Layout.fillWidth: true


                }

                RightPaneLightSwitchComponent {
                    label: "Exhaust Fan"
                    labelColor: "black"
                    Layout.fillWidth: true


                }

                Item { Layout.fillHeight: true }

                Button {
                    id: closeBtn
                    text: "Close"

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 140
                    Layout.preferredHeight: 42

                    background: Rectangle {
                        radius: 14
                        color: "#52BE80"   // green accent
                    }

                    contentItem: Text {
                        text: closeBtn.text
                        anchors.centerIn: parent
                        color: "black"
                        font.bold: true
                        font.pixelSize: 16
                    }

                    onClicked: laundryWindow.close()
                }
            }
        }
    }
}
