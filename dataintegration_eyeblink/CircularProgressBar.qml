import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    id: root

    property int size: 1000 //150
    property int lineWidth: 500//5
    property real value: 0

    property color primaryColor: "#00ff00"//"#29b6f6"
    property color secondaryColor: "#00ff00"//"#e0e0e0"

    property int animationDuration: 100

    width: Screen.width
    height: Screen.height

    onValueChanged: {
        canvas.degree = value * 270;
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

            var x = root.width * 0.214;
            var y = root.height/2.11;

            var radius = root.size;///2; //- root.lineWidth
            var startAngle = (Math.PI/180) * 45;//270;
            var fullAngle = (Math.PI/180) * (270 + 270);//360);
            var progressAngle = (Math.PI/180) * (45 + degree);

            ctx.reset()

            ctx.lineCap = 'round';
            ctx.lineWidth = root.lineWidth;

            /*ctx.beginPath();
            ctx.arc(x, y, radius, startAngle, fullAngle);
            ctx.strokeStyle = root.secondaryColor;
            ctx.stroke();*/

            ctx.beginPath();
            ctx.arc(x, y, radius, startAngle, progressAngle);
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
