import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 400
    height: 120
    title: qsTr("Favorite Group")
    visible: true

    property string name

    signal accepted(string name)

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        TextField {
            id: nameInput
            Layout.fillWidth: true
            text: root.name
            placeholderText: qsTr("Name")
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Item {
                Layout.fillWidth: true
            }

            Button {
                id: cancelButton
                text: qsTr("Cancel")

                onClicked: root.close()
            }

            Button {
                id: createChannelButton
                text: qsTr("OK")

                onClicked: {
                    if (nameInput.length > 0) {
                        root.accepted(nameInput.text)
                        root.close()
                    }
                }
            }
        }
    }
}
