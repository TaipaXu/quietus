import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebEngine

ColumnLayout {
    id: root
    spacing: 0

    required property string url

    signal goHome
    signal titleChanged(string title)
    signal iconChanged(string url)

    Pane {
        Layout.fillWidth: true
        padding: 0

        RowLayout {
            id: header
            width: parent.width
            Layout.alignment: Qt.AlignLeft

            ToolButton {
                width: 50
                height: 50
                icon.source: "qrc:/images/home"
                onClicked: goHome()
            }

            ToolButton {
                width: 50
                height: 50
                icon.source: "qrc:/images/backward"
                enabled: webview.canGoBack
                onClicked: webview.goBack()
            }

            ToolButton {
                width: 50
                height: 50
                icon.source: "qrc:/images/forward"
                enabled: webview.canGoForward
                onClicked: webview.goForward()
            }

            ToolButton {
                width: 50
                height: 50
                icon.source: "qrc:/images/refresh"
                onClicked: webview.reload()
            }

            Item {
                Layout.fillWidth: true
            }
        }
    }


    WebEngineView {
        id: webview
        Layout.fillWidth: true
        height: parent.height - header.height
        url: root.url

        onTitleChanged: {
            root.titleChanged(webview.title)
        }

        onUrlChanged: {
            root.url = webview.url
        }

        onIconChanged: {
            root.iconChanged(webview.icon)
        }
    }
}
