import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform
import utils

ApplicationWindow {
    id: root
    title: qsTr("Quietus")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    visible: false
    width: 310
    height: 500
    x: 0
    y: 0

    required property string name
    required property string favicon
    required property string url
    required property bool mobileMode
    property bool adjusting

    signal home
    signal nameModified(string name)
    signal faviconModified(string url)
    signal urlModified(string url)
    signal mobileModeModified(bool isMobileMode)
    signal adjustDone(int width, int height, int x, int y)

    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "qrc:/images/bg"
        fillMode: Image.PreserveAspectCrop
    }


    ColumnLayout {
        width: parent.width
        height: parent.height

        Row {
            id: header
            Layout.fillWidth: true
            padding: 10

            TextField {
                id: locationInput
                width: parent.width - parent.padding * 2
                background: Rectangle {
                    color: "white"
                    border.color: "gray"
                    border.width: 1
                    radius: 5
                    opacity: 0.2
                }

                placeholderText: qsTr("Location")

                onAccepted: {
                    const isValidUrl = utils.isValidUrl(locationInput.text)
                    if (isValidUrl) {
                        root.url = locationInput.text
                        browserLoader.active = true
                    }
                }
            }
        }

        FavoriteGroups {
            Layout.fillWidth: true
            Layout.preferredHeight: root.height - header.height
        }
    }

    Loader {
        id: browserLoader
        anchors.fill: parent
        active: false

        sourceComponent: Browser {
            name: root.name
            favicon: root.favicon
            url: root.url
            mobileMode: root.mobileMode

            onGoHome: {
                browserLoader.active = false
                root.name = ""
                root.favicon = ""
                root.url = ""
                root.home()
            }

            onTitleChanged: (title) => {
                root.name = title
                root.nameModified(title)
            }

            onIconChanged: (url) => {
                const iconUrl = url.replace("image://favicon/", "")
                root.favicon = iconUrl
                root.faviconModified(iconUrl)
            }

            onUrlChanged: () => {
                root.url = url
                root.urlModified(url)
            }

            onMobileModeChanged: () => {
                root.mobileMode = mobileMode
                root.mobileModeModified(mobileMode)
            }
        }
    }

    AdjustingMask {
        visible: root.adjusting

        onEndAdjust: {
            root.adjusting = false
            root.adjustDone(root.width, root.height, root.x, root.y)
        }
    }

    Utils {
        id: utils
    }

    onActiveChanged: {
        if (active) {
            root.requestActivate();
            raise();
        } else {
            hide()
        }
    }

    onVisibleChanged: {
        if (visible) {
            root.requestActivate();
            raise();
        } else {
            hide()
        }
    }

    onAdjustingChanged: {
        if (root.adjusting) {
            root.flags = Qt.WindowStaysOnTopHint;
        } else {
            root.flags = Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint;
        }
    }

    Connections {
        target: EventBus

        function onEventTriggered(eventName, data) {
            if (eventName === "openUrl") {
                root.url = data
                browserLoader.active = true
            }
        }
    }

    Component.onCompleted: {
        if (root.url.length > 0) {
            browserLoader.active = true
        }
    }
}
