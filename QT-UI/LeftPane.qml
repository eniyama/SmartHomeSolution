import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: leftItem
    width: 370
    height: parent.height
    anchors.left: parent.left

    // ===================== Date / Time =====================
    Item {
        id: dateitem
        height: 150
        width: parent.width
        anchors.top: parent.top

        Text {
            text: Qt.formatDate(currentTime, "yyyy-MM-dd")
            font.pixelSize: 16
            color: textColor
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.topMargin: 24
        }

        Text {
            text: Qt.formatDate(currentTime, "ddd")
            font.pixelSize: 16
            color: textColor
            anchors.top: parent.top
            anchors.right: ampmtxt.right
            anchors.topMargin: 24
        }

        Text {
            id: timetxt
            text: Qt.formatTime(currentTime, "hh:mm")
            font.pixelSize: 64
            color: textColor
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.leftMargin: 24
            anchors.bottomMargin: 24
        }

        Text {
            id: sectxt
            text: ":" + Qt.formatTime(currentTime, "ss")
            font.pixelSize: 24
            color: textColor
            anchors.baseline: timetxt.baseline
            anchors.left: timetxt.right
        }

        Text {
            id: ampmtxt
            text: Qt.formatTime(currentTime, "AP")
            font.pixelSize: 16
            color: textColor
            anchors.baseline: timetxt.baseline
            anchors.left: sectxt.right
            anchors.leftMargin: 8
        }
    }

    // ===================== Today Weather Card =====================
    Rectangle {
        id: todaysweatheritem
        width: parent.width
        height: 260
        radius: 16
        color: glassyBgColor
        anchors.top: dateitem.bottom
        anchors.topMargin: 17

        Text {
            text: qsTr("Today")
            font.pixelSize: 14
            color: textColor
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 24
        }

        Column {
            id: weatherContent
            spacing: 24
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Row {
                spacing: 24
                anchors.horizontalCenter: parent.horizontalCenter

                IconLabel {
                    id: cloudicon
                    width: 24
                    height: 24
                    color: textColor
                    anchors.baseline: tmptxt.baseline
                }

                Text {
                    id: tmptxt
                    text: Math.round(mqttManager.temperature)
                    font.pixelSize: 82
                    color: textColor

                    Text {
                        text: qsTr("°C")
                        font.pixelSize: 12
                        color: textColor
                        anchors.top: parent.top
                        anchors.left: parent.right
                    }
                }

                Text {
                    id: minmaxtxt
                    text: "24/16"
                    font.pixelSize: 14
                    color: textColor
                    anchors.baseline: tmptxt.baseline
                }
            }

            Text {
                id: weathercommentxt
                text: qsTr("Partially Clouded")
                font.pixelSize: 16
                color: textColor
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    // ===================== Bottom Room Buttons =====================
    Rectangle {
        id: locationitem
        radius: 16
        height: 126
        width: parent.width
        color: glassyBgColor
        anchors.bottom: parent.bottom

        Row {
            id: locationitempadded
            anchors.fill: parent
            anchors.margins: 24

            Repeater {
                id: locationrepeater
                model: roomsModel

                delegate: Item {
                    id: roomdelegateitem
                    height: locationitempadded.height
                    width: locationitempadded.width / locationrepeater.model.count

                    property string label
                    property bool isActive: label === activeRoomLabel
                    signal clicked()

                    label: model.label

                    onClicked: {
                        activeRoomLabel = label

                        var component
                        if (label === "Living") {
                            component = Qt.createComponent("LivingPage.qml")
                        } else if (label === "Kitchen") {
                            component = Qt.createComponent("KitchenPage.qml")
                        } else if (label === "Laundry") {
                            component = Qt.createComponent("Laundry.qml")
                        } else if (label === "Bedroom") {
                            component = Qt.createComponent("Bedroom.qml")
                        }

                        if (component.status === Component.Ready) {
                            var window = component.createObject(null) // top-level window
                            if (window !== null) {
                                window.show()
                            } else {
                                console.log("Failed to create window for " + label)
                            }
                        } else {
                            console.log("Component not ready: " + label)
                        }
                    }

                    Column {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 8

                        IconLabel {
                            width: roomdelegateitem.height * 0.5
                            height: width
                            anchors.horizontalCenter: parent.horizontalCenter
                            opacity: roomdelegateitem.isActive ? 1 : 0.5
                        }

                        Text {
                            text: roomdelegateitem.label
                            font.pixelSize: 12
                            color: textColor
                            anchors.horizontalCenter: parent.horizontalCenter
                            opacity: roomdelegateitem.isActive ? 1 : 0.5
                        }

                        Rectangle {
                            width: roomdelegateitem.width * 0.8
                            height: 4
                            radius: 2
                            color: textColor
                            anchors.horizontalCenter: parent.horizontalCenter
                            opacity: roomdelegateitem.isActive ? 1 : 0.5
                        }
                    }

                    MouseArea { anchors.fill: parent; onClicked: roomdelegateitem.clicked() }
                }
            }
        }
    }
}
