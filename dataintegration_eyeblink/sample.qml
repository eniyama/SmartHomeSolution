//import QtQuick 2.9
import QtQuick.Window 2.2

import QtQuick 2.3
import QtQuick.Controls 2.15

//import QtPositioning 5.5
//import QtLocation 5.6
//import QtQuick.Controls 1.4
//import QtQuick.Controls.Styles 1.4
//import QtQuick.Extras 1.4


Rectangle {
    id: root
    visible: true
    width: Screen.width //1024
    height: Screen.height//600
    //width: 1024
    //height: 600
    //title: qsTr("SDV QNX QT Cluster")
    color: "#FFFFFF"

    property int arr: 0//hud_id.arr
    property int arr_bat: 0
    property int arr_temp: 0
    property int icons: 0
    property double ref: 0.01//hud_id.ref
    property double ref_bat: 0.01
    property double ref_temp: 0.01
    //property double ref: 0.01
    Timer{
        id:trip_timer
        repeat: true
        interval:2500
        running: true

        onTriggered: {
            distance.total++;
        }
    }

    Timer{
        id: timer_speed
        repeat: true
        interval:100
        running: true

        onTriggered: {
            if(progress1.speed >= ref  && progress1.speed < ref+ 0.01 ) {
                arr = can_speed.sendSpeed()
                //console.log("sample-val======mjb======="+arr)
                ref = arr/100
                //console.log("ref--======mjb======="+ref)
            }
            if(progress1.speed < ref)
                progress1.speed = progress1.speed + 0.01
            else if(progress1.speed > ref)
                progress1.speed = progress1.speed - 0.01
        }
    }

    Timer{
        id: timer_battery
        repeat: true
        interval:100
        running: true

        onTriggered: {
            //battery
            if(progress3.temp >= ref_bat  && progress3.temp < ref_bat+ 0.01 ) {
                arr_bat = can_speed.sendTemp()
                //console.log("val======mjb_arr_bat======="+arr_bat)
                ref_bat = arr_bat/50
                //console.log("ref--======mjb_ref_bat======="+ref_bat)
            }
            if(progress3.temp < ref_bat)
                progress3.temp = progress3.temp + 0.01
            else if(progress3.temp > ref_bat)
                progress3.temp = progress3.temp - 0.01

            //temperature
            if(progress4.temp >= ref_temp  && progress4.temp < ref_temp+ 0.01 ) {
                arr_temp = can_speed.sendFuel()
                //console.log("val======mjb_temp======="+arr_temp)
                ref_temp = arr_temp/100
                //console.log("ref--======mjb_temp======="+ref_temp)
            }
            if(progress4.temp < ref_temp)
                progress4.temp = progress4.temp + 0.01
            else if(progress4.temp > ref_temp)
                progress4.temp = progress4.temp - 0.01
        }
    }

    Timer{
        id: id_timer_1
        repeat: true
        interval:2000
        running: true
        onTriggered: {
            icons = can_speed.sendIcon()
            engine_oil_icon.eng = icons & 1
            battery_icon.bat = icons & 2
            childlock.child_lock = icons & 4
            seat_belt_icon.seat = icons & 8
            head_light_icon.head_light = icons & 16
            tyre_pressure_icon.tyre = icons & 32
            bulb_icon.bulb = icons & 64
            parking_icon.parking = icons & 128
            union.door = can_speed.sendDoor()

            /*if(engine_oil_icon.eng == true)
                engine_oil_icon.eng = false
            else
                engine_oil_icon.eng = true
            if(seat_belt_icon.seat == true)
                seat_belt_icon.seat = false
            else
                seat_belt_icon.seat = true
            if(battery_icon.bat == false)
                battery_icon.bat = true
            else
                battery_icon.bat = false
            if(tyre_pressure_icon.tyre == true)
                tyre_pressure_icon.tyre = false
            else
                tyre_pressure_icon.tyre = true
            if(childlock.child_lock == true) {
                childlock.child_lock = false
                parking_icon.parking = false
                head_light_icon.head_light = false
                bulb_icon.bulb = false
            } else {
                childlock.child_lock = true
                parking_icon.parking = true
                head_light_icon.head_light = true
                bulb_icon.bulb = true
            }*/
        }
    }
    Image {
        id: frame_1
        width: root.width
        height: root.height
        y: 0
        x: 0
        source: "images/Frame_1.png"
    }
    Image {
        id: background_image
        width: root.width * 0.9912  //1014.988
        height: root.height * 0.8817
        y: root.height * 0.117 //70
       // width: 1015
       // height: 529
        x: 0
        source: "images/Background_image.png"
    }
    Image {
        id: vector_1
        width: root.width
        height: root.height//592
        y: 0
        x: 0
        source: "images/Vector_1.png"
    }
    Image {
        id: vector_2
        //height: 600
        width: root.width
        height: root.height
        opacity: 1
        y: 0
        //width: 1024
        x: 0
        source: "images/Vector_2.png"

        Rectangle {
            id: rectangle
            x: root.width * 0.7393//757
            y: root.height * 0.11//66
            width: root.width * 0.2393 //245
            height: root.height * 0.2584//155
            color: "#1f3352"
            radius: 11
            border.color: "#00000000"
            border.width: 1

            Text {
                id: textEdit
                width: rectangle.width * 0.5 // 775//117
                height: rectangle.height * 0.155//24
                x: rectangle.width/2 - width/2 //69
                y: rectangle.height * 0.72 //112
                color: "#ececec"
                text: qsTr("4th Main road")
                opacity: 0.8
                textFormat: Text.PlainText
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideMiddle
                font.pointSize: rectangle.height * 0.07 //5
            }

            Text{
                id: textEdit1
                width: rectangle.width * 0.28 // 1//59
                height: rectangle.height * 0.194//30
                x: rectangle.width/2 - width/2 //98
                y: rectangle.height * 0.555 //86
                color: "#ececec"
                text: qsTr("300m")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                elide: Text.ElideMiddle
                font.pixelSize: rectangle.height * 0.1 //10
            }
            Image {
                id: arrow
                width: rectangle.width * 0.21 //51.5
                height: rectangle.height * 0.471 //73
                x: rectangle.width/2 - width/2 //83
                y: rectangle.height * 0.052 //8
                source: "images/arrow.png"
            }
        }

    }

    Image {
        property int door: 0
        id: union
        width: root.width * 0.1202 //123
        height: root.height * 0.1//0.0692//41.5
        x: root.width * 0.294//301
        y: root.height * 0.7225 //433.5
        source: door == 1 ? "images/door_1.png" : door == 2 ? "images/door_2.png" : door == 3 ? "images/doors_3.png" : door == 4 ? "images/door_4.png" : door == 8 ? "images/door_8.png" : door == 14 ? "images/doors_14.png" : door == 15 ? "images/doors_15.png" : "images/Union.png"
    }

    Image {
        id: battery_bar
        width: root.width * 0.101 //10254 //105
        height: root.height * 0.22165 //133
        x: root.width * 0.61 //72 //632
        y: root.height * 0.5865 //352
        source: "images/fuel_bar.png"
    }
    Image {
        id: battery
        width: root.width * 0.01751 //17.93
        height: root.height * 0.0317 //19
        x: root.width * 0.5812 //595
        y: root.height * 0.795 //477
        source: "images/battery_icon.png"
    }
    Image {
        id: temp
        width: root.width * 0.0167 //17
        height: root.height * 0.0284 //17
        x: root.width * 0.55947 //572.89
        y: root.height * 0.7684 //461.37
        source: "images/temp.png"
    }
    Image {
        id: temp_bar
        width: root.width * 0.1101 //1153 //118
        height: root.height * 0.19835 //119
        x: root.width *  0.58 //0.585 //599
        y: root.height * 0.5867 //352
        source: "images/temp_bar.png"
    }
    Image {
        id: circle_speed
        width: root.height * 0.5167 //310
        height: root.height * 0.5167 //310
        x: root.width * 0.0069 //7
        y: root.height * 0.28 //168
        source: "images/circle.png"
    }
    Image {
        id: speed_arc
        width: root.height * 0.4167 //250
        height: root.height * 0.4167 //250
        x: root.width * 0.0352 //36
        y: root.height * 0.3 //180
        source: "images/speed_arc.png"
    }
    Image {
        id: circle_rpm
        width: root.height * 0.5167 //310
        height: root.height * 0.5167 //310
        x: root.width * 0.3825 //09 //390
        y: root.height * 0.28 //168
        source: "images/right_circle.png"
    }
    Image {
        id: rpm_arc
        width: root.height * 0.4167 //250
        height: root.height * 0.4167 //250
        x: root.width * 0.4122 //422
        y: root.height * 0.3 //180
        source: "images/rpm_arc.png"
    }
    Image {
        id: music_1
        width: root.width * 0.1719 //176
        height: root.height * 0.1484 //89
        x: root.width * 0.8067 //826
        y: root.height * 0.42 //251
        source: "images/music_1.png"
    }
    Image {
        id: music_2
        width: root.width * 0.137 //140
        height: root.height * 0.1 //60
        x: root.width * 0.842 //862
        y: root.height * 0.57 //341
        source: "images/music_2.png"
    }

    Text {
        id: time_text
        //text: qsTr("17.25")
        x: root.width * 0.0557 //57
        y: root.height * 0.0443 //26
        width: root.width * 0.0811 //83
        height: root.height * 0.09 //54
        color: "#FFFFFF"
        font.pixelSize: root.height * 0.05 //
        text: Qt.formatTime(new Date(),"hh:mm")

        Timer {
            id: timer
            interval: 60000
            repeat: true
            running: true

            onTriggered:
            {
                timeText.text =  Qt.formatTime(new Date(),"hh:mm")
            }
        }

    }

    Image {
        id: side_line
        width: 2
        height: root.height * 0.1134 //68
        y: root.height * 0.03 //18
        x: root.width * 0.1636 //167.5
        visible: true
        source: "images/line.png"
    }
    Image {
        id: weather_icon
        width: root.width * 0.04921 //50.39
        height: root.height * 0.085 //51
        x: root.width * 0.1797 //184
        y: root.height * 0.0417 //25
        source: "images/cloud.png"
    }
    TextEdit {
        property int total: 86669
        id: distance
        x: root.width*0.2968//137
        y: root.height*0.87//109
        width: root.width*0.07714 //79
        height: root.height*0.0333//20
        text: qsTr("Total ") + total + qsTr(" Kms")
        font.pixelSize: root.height*0.025 //15
        color: "white"
        font.family: "Verdana"
    }
    Image {
        id: vector_element_icon
        width: root.width * 0.4649 //476
        height: root.height * 0.1317 //79
        x: root.width * 0.1202 //123
        y: root.height * 0.9117 //547
        source: "images/vector_element_icon.png"
    }
    Image {
        property bool eng: false
        id: engine_oil_icon
        width: root.width * 0.0329 //33.62
        height: root.height * 0.024 //14.41
        x: root.width * 0.16937 //173.43
        y: root.height * 0.9341 //560.45
        source: eng == false ? "images/engine_oil_icon.png" : "images/engine_oil_red.png"

    }
    Image {
        property bool bat: false
        id: battery_icon
        width: root.width * 0.0246 //25.21
        height: root.height * 0.028 //16.81
        x: root.width * 0.22682 //232.26
        y: root.height * 0.9313 //558.77
        source: bat == false ? "images/battery_icon.png" : "images/battery_red.png"
    }
    Image {
        property bool child_lock: false
        id: childlock
        width: root.width * 0.0197 //20.17
        height: root.height * 0.035634 //21.38
        x: root.width * 0.276055 //282.68
        y: root.height * 0.9285 //557.09
        source: child_lock == false ? "images/childlock.png" : "images/childlock_red.png"
    }
    Image {
        property bool parking: false
        id: parking_icon
        width: root.width * 0.02686 //27.5
        height: root.height * 0.03362 //20.17
        x: root.width * 0.3204 //328.06
        y: root.height * 0.9313 //558.77
        source: parking == false ? "images/parking_icon.png" : "images/parking_red.png"
    }
    Image {
        property bool head_light: false
        id: head_light_icon
        width: root.width * 0.02462 //25.21
        height: root.height * 0.0303 //18.17
        x:root.width * 0.37126 //380.17
        y: root.height * 0.9341 //560.45
        source: head_light == false ?"images/lowbeam_off.png" : "images/highbeam_red.png"
    }
    Image {
        property bool tyre: false
        id: tyre_pressure_icon
        width: root.width * 0.0197 //20.17
        height: root.height * 0.0298 //17.84
        x: root.width * 0.42051 //430.6
        y: root.height * 0.9341 //560.45
        source: tyre == false ? "images/tyre_pressure_icon.png" : "images/tyre_pressure_icon_red.png"
    }
    Image {
        property bool bulb: false
        id: bulb_icon
        width: root.width * 0.0197 //20.17
        height: root.height * 0.03362 //20.17
        x: root.width * 0.46483 //475.98
        y: root.height * 0.9313 //558.77
        source: bulb == false ? "images/buld_icon.png" : "images/bulb_on_red.png"
    }
    Image {
        property bool seat: false
        id: seat_belt_icon
        width: root.width * 0.0157 //16.0
        height: root.height * 0.03362 //20.17
        x: root.width * 0.50915 //521.36
        y: root.height * 0.9313 //558.77
        source: seat == false ? "images/seat_lock_icon.png" : "images/seatbelt_red.png"
    }
    Text {
        id: weather_report
        text: qsTr("27\xB0C, Partly Cloudy")
        x: root.width * 0.2383 //244
        y: root.height * 0.07 //42
        width: root.width * 0.184 //188
        height: root.height * 0.05 //30
        color: "#FFFFFF"
        font.pixelSize: root.height * 0.037 //10
    }
    ArcProgressBar {
                id: progress1
                property double speed: 0.01
                x: root.width * 0.03521 //36
                y: root.height * 0.3 //180
                value: progress1.speed
                start_angle_val: 50
                end_angle_val:260
                size: root.height * 0.4167 //250
                width: root.height * 0.4167 //250
                height: root.height * 0.4167 //250
                lineWidth: height * 0.085
                primaryColor: "#29b6f6" //"#00ff00"//

                Text {
                    text: parseInt(progress1.value * 250)
                    anchors.centerIn: parent
                    font.pointSize: 20
                    color: progress1.primaryColor
                }
    }
    ArcProgressBar {
                id: progress2
                property double temp: 0.01
                x: root.width * 0.4122 //422
                y: root.height * 0.3 //180
                value: progress1.value //progress2.temp
                start_angle_val: 130
                end_angle_val:-260
                move:true
                size: root.height * 0.4167 //250
                width: root.height * 0.4167 //250
                height: root.height * 0.4167
                lineWidth: height * 0.085 //20
                primaryColor: "#29b6f6" //"#00ff00"//"#29b6f6"

                Text {
                    text: parseInt(progress1.value * 10600/2)
                    anchors.centerIn: parent
                    font.pointSize: 20
                    color: progress1.primaryColor
                }
    }

    ArcProgressBar {
                id: progress3
                property double temp: 0.01
                x: root.width * 0.4561 //467
                y: root.height * 0.36834 //221
                value: progress3.temp
                start_angle_val: 84
                end_angle_val:-80
                move:true
                size: root.height * 0.4167 //250
                width: root.height * 0.4167 //250
                height: root.height * 0.4167 //250
                lineWidth: height * 0.0365 // 9
                primaryColor: "#29b6f6" //"#00ff00"//"#29b6f6"
    }
    ArcProgressBar {
                id: progress4
                property double temp: 0.01
                x: root.width * 0.4756 //487
                y: root.height * 0.395 //237
                value: progress4.temp
                start_angle_val: 78.5
                end_angle_val:-80
                move:true
                size: root.height * 0.4167 //250
                width: root.height * 0.4167 //250
                height: root.height * 0.4167 //250
                lineWidth: height * 0.0365 // 9
                primaryColor: "#29b6f6" //"#00ff00"//"#29b6f6"
    }
}
