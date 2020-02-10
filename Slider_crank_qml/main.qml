import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property int val: 0

    RowLayout{
        spacing: 20

        anchors.fill: parent

        MouseArea{
            anchors.fill: parent

            onWheel: {
                val = val + wheel.angleDelta.y/120;
                console.log(val)

                if (val > 360)
                    val = val % 360
                else if (val < 0)
                    val = val + 360
                first.angle = val;
                second.angle = val+90;
                third.angle = val+180;
                fourth.angle = val+270;

            }
        }

        SliderCrank{
            id: first

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
        }

        SliderCrank{
            id:second

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
        }

        SliderCrank{
            id: third

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
        }

        SliderCrank{
            id: fourth

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
        }

    }


}
