import QtQuick 2.0

Item {

    id:annimation_values

    property real kph: 0
    property real litres: 40

//    SequentialAnimation {
    ParallelAnimation {
        running: true
        loops: 1

        // We want a small pause at the beginning, but we only want it to happen once.
        PauseAnimation {
            duration: 1000
        }

       /* PropertyAction {
            target: annimation_values
            property: "start"
            value: false
        }*/
        SequentialAnimation {
            loops: Animation.Infinite

        ParallelAnimation{
            NumberAnimation{
            target: annimation_values
            property: "kph"
            easing.type: Easing.InOutSine
            from: 0
            to: 95
            duration: 5000
            }
        }
        ParallelAnimation{
            NumberAnimation{
            target: annimation_values
            property: "kph"
            easing.type: Easing.InOutSine
            from: 95
            to: 0
            duration: 5000
            }
        }
		}

        SequentialAnimation {
            loops: Animation.Infinite

        ParallelAnimation{

            NumberAnimation {
                target: annimation_values
                property: "litres"
                from: 40
                to: 30
                duration: 15000
                easing.type: Easing.InOutSine
            }
        }

        ParallelAnimation{

            NumberAnimation {
                target: annimation_values
                property: "litres"
                from: 30
                to: 40
                duration: 5000
                easing.type: Easing.InOutSine
            }
        }
		}

    }
}

