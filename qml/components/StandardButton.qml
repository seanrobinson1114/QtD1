import QtQuick 1.1

Rectangle {
    id: button

    property string text: "button"
    property color textColor: "red"
    property int textSize: 24
    property bool textBold: false

    signal buttonClicked
    signal buttonEntered
    signal buttonExited

    Text {
        id: button_text
        anchors.horizontalCenter: button.horizontalCenter
        anchors.verticalCenter: button.verticalCenter

        text: button.text
        font.pointSize: button.textSize
        color: button.textColor
        font.bold: button.textBold
    }

    MouseArea {
        id: button_mouse_area
        anchors.fill: button
        onClicked: button.buttonClicked()
        onEntered: button.buttonEntered()
        onExited: button.buttonExited()
    }
}
