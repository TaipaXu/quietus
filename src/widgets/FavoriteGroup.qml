import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import model.favoriteGroup as Model

ColumnLayout {
    id: root
    width: parent.width
    spacing: 10

    property Model.FavoriteGroup favoriteGroup

    RowLayout {
        width: parent.width
        anchors.bottomMargin: 10

        Label {
            Layout.fillWidth: true
            text: favoriteGroup.name
            font.pixelSize: 17

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
            }
        }

        ToolButton {
            id: editButton
            width: 50
            height: 50
            icon.source: "qrc:/images/edit"
            hoverEnabled: true
            opacity: mouseArea.containsMouse || hovered ? 1 : 0

            onClicked: {
                addEditFavoriteGroupDialogLoader.sourceComponent = addEditFavoriteGroupDialogComponent
                addEditFavoriteGroupDialogLoader.item.name = favoriteGroup.name
                addEditFavoriteGroupDialog.active = true
            }
        }

        ToolButton {
            id: removeButton
            width: 50
            height: 50
            icon.source: "qrc:/images/remove"
            hoverEnabled: true
            opacity: mouseArea.containsMouse || hovered ? 1 : 0

            onClicked: {
                confirmationDialog.open()
            }
        }

        ToolButton {
            id: addButton
            width: 50
            height: 50
            icon.source: "qrc:/images/add"
            hoverEnabled: true
            opacity: mouseArea.containsMouse || hovered ? 1 : 0

            onClicked: {
                favoriteDialogLoader.sourceComponent = favoriteDialogComponent
                favoriteDialogLoader.active = true
            }
        }
    }

    Flow {
        Layout.fillWidth: true
        width: parent.width

        Repeater {
            model: favoriteGroup.websites
            delegate: Favorite {
                website: modelData
            }
        }
    }

    Component {
        id: favoriteDialogComponent

        FavoriteDialog {
            id: favoriteDialog
            name: root.name
            favicon: root.favicon
            url: root.url

            onAccepted: (groupId, name, favicon, url) => {
                FavoriteLink.addFavoriteWebsite(groupId, name, favicon, url);
            }

            onClosing: {
                favoriteDialogLoader.sourceComponent = undefined
            }
        }
    }

    Loader {
        id: favoriteDialogLoader
    }

    Component {
        id: addEditFavoriteGroupDialogComponent

        AddEditFavoriteGroupDialog {
            id: addEditFavoriteGroupDialog

            onAccepted: (name) => {
                FavoriteLink.editFavoriteGroup(favoriteGroup.id, name)
            }

            onClosing: {
                addEditFavoriteGroupDialogLoader.sourceComponent = undefined
            }
        }
    }

    Loader {
        id: addEditFavoriteGroupDialogLoader
    }

    MessageDialog {
        id: confirmationDialog
        text: qsTr("Confirm Deletion")
        informativeText: qsTr("Are you sure you want to delete this item?")
        buttons: MessageDialog.Ok | MessageDialog.Cancel

        onAccepted: {
            FavoriteLink.removeFavoriteGroup(favoriteGroup.id)
        }

        onRejected: {

        }
    }
}
