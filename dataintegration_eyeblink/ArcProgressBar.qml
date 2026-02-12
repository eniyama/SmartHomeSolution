import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    id: root

    property int size: 250 //150
    property int lineWidth: 20//5
    property real value: 0

    property color primaryColor: "#00ff00"
    property color secondaryColor: "#00ff00"
    property int animationDuration: 100

    property double start_angle_val: 0
    property double end_angle_val: 0
    property bool move: false

    width: 250
    height: 250

    onValueChanged: {
        canvas.degree = value * end_angle_val;
    }

    Canvas {
        id: canvas

        property real degree: 0

        anchors.fill: parent
        antialiasing: true

        onDegreeChanged: {
            requestPaint();
        }

        onPaint: {
            var ctx = getContext("2d");
/*
            var x = root.width/2;
            var y = root.height * 0.55;

            var radius = root.width * 0.5;///2; //- root.lineWidth
            var startAngle = (Math.PI/180) * 45;//270;
            var fullAngle = (Math.PI/180) * (270 + 270);//360);
            var progressAngle = (Math.PI/180) * (45 + degree);*/
            var x = root.width/2;
            var y = root.height/2;
            var radius = root.size/2 - root.lineWidth/2;///2; //- root.lineWidth
            var startAngle = (Math.PI/180) * start_angle_val;//270;
            var fullAngle = (Math.PI/180) * (270 + 360);//360);
            var progressAngle = (Math.PI/180) * (start_angle_val + degree);

            //original full circle
            /*var radius = root.size/2 - root.lineWidth/2
            var startAngle = (Math.PI/180) * 270;
            var fullAngle = (Math.PI/180) * (270 + 360);
            var progressAngle = (Math.PI/180) * (270 + degree);*/

            ctx.reset()

            ctx.lineCap = 'round';
            ctx.lineWidth = root.lineWidth;

            /*ctx.beginPath();
            ctx.arc(x, y, radius, startAngle, fullAngle);
            ctx.strokeStyle = root.secondaryColor;
            ctx.stroke();*/

            ctx.beginPath();
            ctx.arc(x, y, radius, startAngle, progressAngle, move);
            ctx.strokeStyle = root.primaryColor;
            ctx.stroke();
        }

        Behavior on degree {
            NumberAnimation {
                duration: root.animationDuration
            }
        }
    }
}
