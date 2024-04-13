import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 400
    height: 200
    title: qsTr("Favorite")
    visible: true

    property string name
    property string favicon
    property string url

    property string groupId

    signal accepted(string groupId, string name, string favicon, string url)

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

        TextField {
            id: urlInput
            Layout.fillWidth: true
            text: root.url
            placeholderText: qsTr("Url")
        }

        ComboBox {
            id: groupSelector
            Layout.fillWidth: true
            model: FavoriteLink.favoriteGroups
            textRole: "name"

            onCurrentValueChanged: {
                groupId = currentValue.id
            }
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
                    if (nameInput.length > 0 && urlInput.length > 0 && groupSelector.currentIndex > -1) {
                        root.accepted(groupId, nameInput.text, root.favicon, urlInput.text)
                        root.close()
                    }
                }
            }
        }
    }
}
