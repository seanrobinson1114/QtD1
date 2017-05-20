import QtQuick 1.1
import "../"

Rectangle {
    id: button

    signal upButtonClicked
    signal downButtonClicked

    Rectangle {
        id: button_container
        width: 17
        height: 34
        anchors.horizontalCenter: button.horizontalCenter
        anchors.verticalCenter: button.verticalCenter
        
        ScrollButton {
            id: up_button
            anchors.top: parent.top
            anchors.left: parent.left
            
            up: true
            
            onButtonClicked: button.upButtonClicked()
        }

        ScrollButton {
            id: down_button
            anchors.top: up_button.bottom
            anchors.left: parent.left
            
            up: false
            
            onButtonClicked: button.downButtonClicked()
        }
    }
}
