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

    required property string id
    required property string name
    required property string favicon
    required property string url
    required property bool mobileMode

    signal home
    signal nameModified(string name)
    signal faviconModified(string url)
    signal urlModified(string url)
    signal mobileModeModified(bool isMobileMode)

    ColumnLayout {
        width: parent.width

        Row {
            Layout.fillWidth: true
            padding: 10

            TextField {
                id: locationInput
                width: parent.width - parent.padding * 2

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
    }

    Loader {
        id: browserLoader
        anchors.fill: parent
        active: false

        sourceComponent: Browser {
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

    Component.onCompleted: {
        if (root.url.length > 0) {
            browserLoader.active = true
        }
    }
}