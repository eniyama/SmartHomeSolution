import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: kitchenWindow
    width: 400
    height: 600
    visible: false
    title: "Kitchen Devices"

    Rectangle {
        anchors.fill: parent
        color: "#2C3E50"

        Rectangle {
            id: cardPanel
            width: parent.width * 0.82
            height: parent.height * 0.78
            radius: 24
            anchors.centerIn: parent

            color: "#ECF0F1CC"
            border.width: 1
            border.color: "#BDC3C7"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 20

                // Title
                Text {
                    text: "Kitchen Appliances"
                    font.pixelSize: 20
                    font.bold: true
                    color: "#2C3E50"
                    Layout.alignment: Qt.AlignHCenter
                }

                // Divider
                Rectangle {
                    height: 1
                    color: "#BDC3C7"
                    Layout.fillWidth: true
                }

                // Appliances switches using the same RightPaneLightSwitchComponent
                RightPaneLightSwitchComponent {
                    label: "Refrigerator"
                    labelColor: "black"
                    Layout.fillWidth: true
                }

                RightPaneLightSwitchComponent {
                    label: "Mixer"
                    labelColor: "black"
                    Layout.fillWidth: true
                }

                RightPaneLightSwitchComponent {
                    label: "Coffee Maker"
                    labelColor: "black"
                    Layout.fillWidth: true
                }

                RightPaneLightSwitchComponent {
                    label: "Microwave Oven"
                    labelColor: "black"
                    Layout.fillWidth: true
                }

                // Spacer
                Item { Layout.fillHeight: true }

                // Close Button
                Button {
                    id: closeBtn
                    text: "Close"
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 140
                    Layout.preferredHeight: 42

                    background: Rectangle {
                        radius: 14
                        color: "#E74C3C"
                    }

                    contentItem: Text {
                        text: closeBtn.text
                        anchors.centerIn: parent
                        color: "black"
                        font.bold: true
                        font.pixelSize: 16
                    }

                    onClicked: kitchenWindow.close()
                }
            }
        }
    }
}
