import QtQuick 2.3
import QtQuick.Controls 2.15

//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4
//import QtQuick.Extras 1.4
import QtQuick.Window 2.0


Item {
    visible: true
    id: hud_id
    x: 0
    y: 0
    width: Screen.width
    height: Screen.height
    property int maximumLength: 100
    property real progress: 0
    property bool reverseAnimation: false
    property int arr: 0
    property int arr_bat: 0
    property int ref_bat: 0
    property double ref: 0.01
    Timer{
        id: id_timer_1
        repeat: true
        interval:25000
        running: true

        onTriggered: {
            progress_1.temp = 0.01
            progress = 1
        }
    }
    Timer{
        id: id_timer_2
        repeat: true
        interval:2000
        running: true
        onTriggered: {
            path_arrow.door = can_speed.sendDoor()
        }
    }

    Timer{
        id: id_timer
        repeat: true
        interval:100
        running: true

        onTriggered: {
            /*if(progress_1.temp < 1) {
                progress_1.temp = progress_1.temp + 0.01
                progress++
                //progressBar.progress++
                //progress2.temp = progress2.temp + 0.01
            }else{
                progress_1.temp = 0
                progress=1
                //progressBar.progress = 0
                //progress2.temp = 0
            }*/
            if(progress_1.temp >= ref  && progress_1.temp < ref+ 0.01 ) {
                arr = can_speed.sendSpeed()
                //console.log("hud-val======mjb======="+arr)
                ref = arr/100
                //console.log("hud-ref--======mjb======="+ref)
            }
            if(progress_1.temp < ref)
                progress_1.temp = progress_1.temp + 0.01
            else if(progress_1.temp > ref)
                progress_1.temp = progress_1.temp - 0.01

            if(progress == arr_bat) {
                arr_bat = can_speed.sendFuel()
                //console.log("hud-bat======mjb======="+arr)
                ref_bat = arr_bat ///100
                //console.log("hud-ref--======mjb======="+ref)
            }
            if(progress < ref_bat)
                progress = progress + 1
            else if(progress > ref_bat)
                progress = progress - 1

        }
    }


 Image {
    id: bg_image
    x: 0
    y: 0
    width: hud_id.width//510
    height: hud_id.height//280
    source: "images_4/BG_image.png"
    //fillMode: Image.PreserveAspectFit
}

Image {
    id: bg_1
    width: hud_id.width//510
    height: hud_id.height//280
    source: "images_4/bg_1.png"
    //fillMode: Image.PreserveAspectFit

    Image {
        id: path_blue
        x: bg_1.width*0.3431//175
        y: bg_1.height*0.5535//155
        width: bg_1.width*0.3158//161
        height:bg_1.height*0.3857//108
        source: "images_4/path_blue.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        property int door: 0
        id: path_arrow
        x: bg_1.width*0.3784//193
        y: bg_1.height*0.7142//200
        width: bg_1.width*0.2411//123
        height: bg_1.height*0.15//42
        source: door == 1 ? "images/door_1.png" : door == 2 ? "images/door_2.png" : door == 3 ? "images/doors_3.png" : door == 4 ? "images/door_4.png" : door == 8 ? "images/door_8.png" : door == 14 ? "images/doors_14.png" : door == 15 ? "images/doors_15.png" : "images_4/path_arrow.png"
        //source: "images_4/path_arrow.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: path_leftline
        x: bg_1.width*0.2823//144
        y: bg_1.height*0.5214//146
        width: bg_1.width*0.2490//127
        height:bg_1.height*0.4785// 134
        source: "images_4/path_leftline.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: path_rightline
        x: bg_1.width*0.4705//240
        y: bg_1.height*0.525//147
        width: bg_1.width*0.2490//127
        height: bg_1.height*0.4785//134
        source: "images_4/path_rightline.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
            id: rect_d
            x: bg_1.width*0.757 //68//386
            y: bg_1.height*0.68 //687//187
            width: bg_1.width*0.0882//45
            height: bg_1.height*0.1607//45
            source: "images_4/rect_d.png"
            fillMode: Image.PreserveAspectFit

            Text {
                id: text7
                x: rect_d.width*0.37 //82//17
                y: rect_d.height*0.015//5
                width: rect_d.width*0.3333//15
                height:rect_d.height*0.5333//24
                color: "#ff0000"
                text: qsTr("D")
                font.pixelSize: hud_id.height * 0.075 //40
                font.weight: Font.Bold
                font.family: "Verdana"
            }
    }

    /*Image {
        id: battery_max
        x: bg_1.width*0.8039//410
        y: bg_1.height*0.3964//111
        width: bg_1.width*0.2058//105
        height: bg_1.height*0.45//126
        source: "images_4/battery_max.png"
        fillMode: Image.PreserveAspectFit
    }*/

    Image {
        id: petrol_max
        x: bg_1.width*-0.0058//-3
        y: bg_1.height*0.4178//117
        width: bg_1.width*0.1843//94
        height: bg_1.height*0.4178//117
        source: "images_4/petrol_max.png"
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: speed_max
        x: bg_1.width*0.1490//76
        y: bg_1.height*0.5285//148
        width: bg_1.height*0.3214//90
        height: bg_1.height*0.3214//90
        source: "images_4/speed_arc.png"
        //fillMode: Image.PreserveAspectFit
        }
    ArcProgressBar {
        id: progress_1
        property double temp: 0.01
        x:bg_1.width*0.1490
        y:bg_1.height*0.5285
        value: progress_1.temp
        start_angle_val: 50
        end_angle_val:260
        size: bg_1.height*0.3214 //250
        width: bg_1.height*0.3214 //250
        height: bg_1.height*0.3214 //250
        lineWidth: height * 0.08
        primaryColor: "#64D483" //"#00ff00"//

        Text {
            text: parseInt(progress_1.value * 250) + qsTr("km/h")
            anchors.centerIn: parent
            font.pointSize: bg_1.height*0.04//20
            color: "#FFFFFF"
        }
    }
    }

    Image {
        id: battery
        x: bg_1.width*0.0666//34
        y: bg_1.height*0.2678//75
        width: bg_1.width*0.0450//23
        height: bg_1.height*0.0821//23
        source: "images_4/battery.png"
        fillMode: Image.PreserveAspectFit
    }

    /*Image {
        id: battery
        x: bg_1.width*0.8823//450
        y: bg_1.height*0.275//77
        width: bg_1.width*0.0509//26
        height: bg_1.height*0.0928//26
        source: "images_4/battery.png"
        fillMode: Image.PreserveAspectFit
    }*/

    Text {
        id: text3
        x: bg_1.width*0.7921//404
        y: bg_1.height*0.4285//120
        width: bg_1.width*0.0196//10
        height:bg_1.height*0.0714//20
        color: "#ffffff"
        text: qsTr("P")
        font.pixelSize: hud_id.height * 0.065 //35
        //font.family: "Verdana"
    }

    Text {
        id: text4
        x: bg_1.width*0.7921//404
        y: bg_1.height*0.5071//142
        width: bg_1.width*0.0235//12
        height: bg_1.height*0.0535//15
        color: "#ffffff"
        text: qsTr("R")
        font.pixelSize: hud_id.height * 0.065 //35
        //font.family: "Verdana"
    }

    Text {
        id: text5
        x: bg_1.width*0.7921//404
        y: bg_1.height*0.5857//164
        width:bg_1.width*0.0254//13
        height:bg_1.height*0.0714//20
        color: "#ffffff"
        text: qsTr("N")
        font.pixelSize: hud_id.height * 0.065 //35
        //font.family: "Verdana"
    }

    Text {
        id: text6
        x: bg_1.width*0.7921//404
        y: bg_1.height*0.7857//220
        width:bg_1.width*0.0196//10
        height:bg_1.height*0.0714//20
        color: "#ffffff"
        text: qsTr("L")
        font.pixelSize: hud_id.height * 0.065 //35
        //font.family: "Verdana"
    }


Image {
    id: rect_arrow
    x: bg_1.width*0.3098//158
    y: bg_1.height*0.0821//23
    width: bg_1.width*0.3764//192
    height: bg_1.height*0.475//133
    source: "images_4/rect_arrow.png"
    fillMode: Image.PreserveAspectFit

    Image {
        id: arrow
        x: rect_arrow.width*0.2968//57
        y: rect_arrow.height*0.0225//3
        width: rect_arrow.width*0.2864//55
        height: rect_arrow.height*0.4135//55
        source: "images_4/arrow2.png"
        fillMode: Image.PreserveAspectFit
     }

    Text {
        id: text1
        x: rect_arrow.width*0.4427//85
        y: rect_arrow.height*0.4661//62
        width: rect_arrow.width*0.2083//40
        height:rect_arrow.height*0.1278//17
        color: "#ffffff"
        text: qsTr("300m")
        font.pixelSize: hud_id.height * 0.05 //32
        //font.weight: Font.Normal
        //font.family: "Verdana"
    }

    Text {
        id: text2
        x: rect_arrow.width*0.3385//65
        y: rect_arrow.height*0.6390//85
        width: rect_arrow.width*0.4843//93
        height:rect_arrow.height*0.1203//16
        color: "#ffffff"
        text: qsTr("4th Main Road")
        font.pixelSize: hud_id.height * 0.05 //32
        //font.family: "Verdana"
    }
}
Item {
    x: hud_id.width * 0.091
    y: hud_id.height * 0.835
    width: petrol_max.width * 0.0529 //18
    height: petrol_max.height
    Rectangle {
        id: progressBar
        width: parent.width
        height: parent.height * (progress / maximumLength)
        radius: width / 2
        color: "#64D483"
        transformOrigin: Item.Bottom
        transform: Rotation { angle: 180 }
        Behavior on height {
            NumberAnimation {
            duration: 100 // Adjust the duration as needed
            }
        }
    }
}
}
