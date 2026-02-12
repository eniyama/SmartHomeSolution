import QtQuick 2.3
import QtQuick.Controls 2.15
//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4
//import QtQuick.Extras 1.4
import QtQuick.Window 2.0

Rectangle {
    id: root
    width: Screen.width //1024
    height: Screen.height//600
    color: "#FFFFFF"
    //color: "gray"

    Loader {
        id: myLoader
        anchors.fill: parent
        source: "MyText.qml"
    }
    property var arr;
    Timer{
        id: id_timer
        repeat: true
        interval:25000
        running: true

        onTriggered: {
           /* arr = can_speed.sendFrame()
            if(arr === "ste") {
                myLoader.source = "sample.qml"
                //console.log("val======main.qml=======")
            } else {
                myLoader.source = "MyText.qml"
                //console.log("val======main.qml_2nd=======")
            }
            //console.log("val======main.qml_outside=======")
            */
            if(myLoader.source == "qrc:/MyText.qml"){
                myLoader.sourceComponent = null
                myLoader.source = "sample.qml"
            }else if(myLoader.source == "qrc:/sample.qml"){
                myLoader.sourceComponent = null
                myLoader.source = "MyText.qml"
            }
        }
    }
}
