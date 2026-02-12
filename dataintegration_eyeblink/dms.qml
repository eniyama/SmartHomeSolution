import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4


Rectangle {
    id: root
    visible: true
    width: Screen.width
    height: Screen.height
    color: "#081C33"
    //title: qsTr("Hello World")
   /* Timer{
        id: id_timer
        repeat: true
        interval:100
        running: true

        onTriggered: {
            if(progress1.temp < 1) {
            progress1.temp = progress1.temp + 0.01
            mjb.te = mjb.te + 5
            }else
                progress1.temp = 0
        }
    }*/

   /* Item {
        id: container
        width: root.width
        height: Screen.height //Math.min(root.width, root.height)
        transformOrigin: Item.Center
        anchors.centerIn: parent
        */

        /*Image {
            id: background
            width: root.width
            height: root.height
           // y: root.height * 0.17
            //x: root.width * 0.63
            source: "images_3/color.png"
        }*/
        Image {
            id: left_arc
            width: root.width * 0.2
            height: root.height * 0.4
            y: root.height/3.25
            x: root.width/2 - width * 2
            source: "images_3/left_clr_arc.png"
            smooth: true
        }
        Image {
            id: right_arc
            width: root.width * 0.2
            height: root.height * 0.4
            y: root.height/3.25
            x: root.width/2 + width
            source: "images_3/right_arc.png"
        }
        Image {
            id: left_gauge
            width: root.width * 0.23//0.235
            height: root.height * 0.399
            y: root.height/2.98
            x: root.width * 0.1
            source: "images_3/left_gauge.png"
        }
        Image {
            id: right_gauge
            width: root.width * 0.235
            height: root.height * 0.4
            y: root.height/3
            x: root.width/1.5
            source: "images_3/right_gauge.png"
        }
        Image {
            id: base
            width: root.width * 0.3
            height: root.height * 0.2
            y: root.height/1.5
            x: root.width/3
            source: "images_3/base.png"
        }
   /*     CircularProgressBar {
                    id: progress1
                    property double temp: 0.01
                    lineWidth: 20
                    value: progress1.temp
                    size: 188
                    //secondaryColor: "#00ff00"//"#e0e0e0"
                    primaryColor: "#00ff00"//"#29b6f6"

                    Text {
                        text: parseInt(progress1.value * 100) + "%"
                        anchors.centerIn: parent
                        font.pointSize: 20
                        color: progress1.primaryColor
                    }
        }
        ProgressBar {
            id: mjb
            property int  te: 1
            value: mjb.te
            x: 100
            y:200
            width: 40
            height: 50
            style: ProgressBarStyle {
                background: Rectangle {
                    radius: 2
                    color: "lightgray"
                    border.color: "gray"
                    border.width: 1
                    implicitWidth: 200
                    implicitHeight: 24
                }
                progress: Rectangle {
                    color: "lightsteelblue"
                    border.color: "steelblue"
                }
            }
        } */
    //}
 }
