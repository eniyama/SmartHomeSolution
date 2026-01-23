import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: bedroomWindow
    width: 400
    height: 600
    visible: false
    title: "Bedroom Devices"

    Rectangle {
        anchors.fill: parent
        color: "#1E3A5F"     // Deep night-blue

        Rectangle {
            id: cardPanel
            width: parent.width * 0.82
            height: parent.height * 0.78
            radius: 24
            anchors.centerIn: parent

            color: "#F5FAFFCC"        // soft frosted blue
            border.width: 1
            border.color: "#A7C6E4"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                Text {
                    text: "Bedroom Appliances"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#123B5A"
                    Layout.alignment: Qt.AlignHCenter
                }

                Rectangle { height: 1; color: "#A7C6E4"; Layout.fillWidth: true }

                RightPaneLightSwitchComponent {
                    label: "Ceiling Light"
                    labelColor: "black"
                    Layout.fillWidth: true


                }

                RightPaneLightSwitchComponent {
                    label: "Bed Lamp"
                    labelColor: "black"
                    Layout.fillWidth: true


                }

                RightPaneLightSwitchComponent {
                    label: "Fan"
                    labelColor: "black"
                    Layout.fillWidth: true
                }

                RightPaneLightSwitchComponent {
                    label: "Air Conditioner"
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
                        color: "#4AA3FF"   // calm blue accent
                    }

                    contentItem: Text {
                        text: closeBtn.text
                        anchors.centerIn: parent
                        color: "black"
                        font.bold: true
                        font.pixelSize: 16
                    }

                    onClicked: bedroomWindow.close()
                }
            }
        }
    }
}
