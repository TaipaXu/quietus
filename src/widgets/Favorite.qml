import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import model.website as Model

Item {
    id: root
    width: 50
    height: 50

    property Model.Website website

    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "transparent"
        radius: 8

        ColumnLayout {
            anchors.fill: parent
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            Image {
                source: "qrc:/images/website"
                Layout.preferredWidth: 20
                Layout.preferredHeight: 20
                Layout.alignment: Qt.AlignHCenter
                fillMode: Image.PreserveAspectFit
            }

            Label {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                text: root.website.name
                font.pixelSize: 10
                elide: Text.ElideRight
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor

            onClicked: {
                EventBus.triggerEvent("openUrl", root.website.url)
            }
        }
    }

    ToolButton {
        id: removeButton
        icon.source: "qrc:/images/remove"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: -7
        width: 20
        height: 20
        padding: 2
        hoverEnabled: true
        visible: mouseArea.containsMouse || hovered

        onClicked: {
            removeFavoriteWebsiteConfirmationDialog.open()
        }
    }

    ToolButton {
        id: editButton
        icon.source: "qrc:/images/edit"
        anchors.top: removeButton.bottom
        anchors.left: removeButton.left
        anchors.topMargin: 1
        width: 20
        height: 20
        padding: 2
        hoverEnabled: true
        visible: mouseArea.containsMouse || hovered

        onClicked: {
            favoriteDialogLoader.sourceComponent = favoriteDialogComponent
            favoriteDialogLoader.active = true
        }
    }

    MessageDialog {
        id: removeFavoriteWebsiteConfirmationDialog
        text: qsTr("Confirm Deletion")
        informativeText: qsTr("Are you sure you want to delete this item?")
        buttons: MessageDialog.Ok | MessageDialog.Cancel

        onAccepted: {
            FavoriteLink.removeFavoriteWebsite(root.website.url)
        }

        onRejected: {

        }
    }

    Component {
        id: favoriteDialogComponent

        FavoriteDialog {
            id: favoriteDialog
            name: root.website.name
            favicon: root.website.favicon
            url: root.website.url

            onAccepted: (groupId, name, favicon, url) => {
                FavoriteLink.editFavoriteWebsite(website.id, groupId, name, favicon, url);
            }

            onClosing: {
                favoriteDialogLoader.sourceComponent = undefined
            }
        }
    }

    Loader {
        id: favoriteDialogLoader
    }
}
