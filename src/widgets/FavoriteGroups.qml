import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Flickable {
    flickableDirection: Flickable.VerticalFlick
    contentHeight: content.height
    topMargin: 0
    clip: true
    ScrollBar.vertical: ScrollBar {}

    Pane {
        id: content
        width: parent.width
        topPadding: 0
        background: null

        ColumnLayout {
            width: parent.width
            spacing: 6

            RowLayout {
                Layout.fillWidth: true

                Label {
                    Layout.fillWidth: true
                    text: qsTr("Favorites")
                    font.bold: true
                    font.pointSize: 20

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                ToolButton {
                    id: addButton
                    width: 50
                    height: 50
                    icon.source: "qrc:/images/add"
                    hoverEnabled: true
                    opacity: mouseArea.containsMouse || hovered ? 1 : 0

                    onClicked: {
                        addEditFavoriteGroupDialogLoader.sourceComponent = addEditFavoriteGroupDialogComponent
                        addEditFavoriteGroupDialogLoader.active = true
                    }
                }
            }

            Repeater {
                model: FavoriteLink.favoriteGroups
                delegate: FavoriteGroup {
                    favoriteGroup: modelData
                }
            }
        }
    }

    Component {
        id: addEditFavoriteGroupDialogComponent

        AddEditFavoriteGroupDialog {
            id: addEditFavoriteGroupDialog

            onAccepted: (name) => {
                FavoriteLink.addFavoriteGroup(name);
            }

            onClosing: {
                addEditFavoriteGroupDialogLoader.sourceComponent = undefined
            }
        }
    }

    Loader {
        id: addEditFavoriteGroupDialogLoader
    }
}
