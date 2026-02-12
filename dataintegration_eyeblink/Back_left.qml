import QtQuick 2.0

Item {
    id: id_root2
    property bool value2: true

    Rectangle {
        id: id_door2
        Image {
            id: new_back_left
            width: root.width * 0.7
            height: root.height * 0.4
            y: root.height * 0.365
            x: root.width * 0.151
            source: value2 == true ? "../cluser_demo_images/leftt.png" : ""

        }
    }

   /*  Rectangle {
       id: door2
       height: parent.height * 0.18
       width: parent.width * 0.6
       x : -width
       y : parent.height * 0.35
       color: value2 == false ? "green" : "red"
       border.color: "sky blue"
    }
   Text {
       anchors.centerIn: door2
       color: "white"
       text: "Back Left"
   }*/

}



