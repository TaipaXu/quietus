import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtWebEngine

ColumnLayout {
    id: root
    spacing: 0

    required property string url
    required property bool mobileMode

    signal goHome
    signal titleChanged(string title)
    signal iconChanged(string url)

    property string desktopUserAgent: "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0"
    property string mobileUserAgent: "Mozilla/5.0 (iPhone; CPU iPhone OS 16_6 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.6 Mobile/15E148 Safari/604.1 Edg/122.0.0.0"

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

            ToolButton {
                width: 50
                height: 50
                icon.source: root.mobileMode ? "qrc:/images/mobile" : "qrc:/images/desktop"
                onClicked: {
                    root.mobileMode = !root.mobileMode
                    if (mobileMode) {
                        webProfile.httpUserAgent = root.mobileUserAgent
                    } else {
                        webProfile.httpUserAgent = root.desktopUserAgent
                    }
                    webview.reload()
                }
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
        profile: webProfile

        onTitleChanged: {
            root.titleChanged(webview.title)
        }

        onUrlChanged: {
            root.url = webview.url
        }

        onIconChanged: {
            root.iconChanged(webview.icon)
        }

        onLoadingChanged: (loadingInfo) => {
            if (root.mobileMode && loadingInfo.status === WebEngineView.LoadSucceededStatus) {
                const css = `
                    html::-webkit-scrollbar {
                        width: 5px;
                    }
                    html::-webkit-scrollbar-track {
                        background: #f1f1f1;
                    }
                    html::-webkit-scrollbar-thumb {
                        background: #888;
                    }
                    html::-webkit-scrollbar-thumb:hover {
                        background: #555;
                    }
                `;
                const js = `{
                    const style = document.createElement('style');
                    style.innerHTML = \`${css}\`;
                    document.head.appendChild(style);
                }`;
                webview.runJavaScript(js);
            }
        }
    }

    WebEngineProfile {
        id: webProfile
        httpUserAgent: root.mobileMode ? root.mobileUserAgent : root.desktopUserAgent
    }
}
