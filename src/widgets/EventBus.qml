pragma Singleton
import QtQuick

QtObject {
    signal eventTriggered(string eventName, var data)

    function triggerEvent(eventName, data) {
        eventTriggered(eventName, data)
    }
}
