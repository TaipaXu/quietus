import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    width: parent.width
    height: parent.height
    color: "#80000000"
    signal endAdjust

    Image {
        anchors.centerIn: parent
        width: 20
        height: 20
        source: "qrc:/images/resize"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: endAdjust()
        }
    }
}
