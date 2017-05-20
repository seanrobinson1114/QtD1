import QtQuick 1.1
import QtD1 1.0

Rectangle {
    id: button

    property string defaultText: "button"
    property string defaultTextFont: "QtD1Gold42"

    property string enteredText: defaultText
    property string enteredTextFont: defaultTextFont
    
    signal buttonClicked
    signal buttonDoubleClicked
    signal buttonEntered
    signal buttonExited

    BitmapText {
        id: default_button_text
        anchors.fill: parent

        text: button.defaultText
        font: button.defaultTextFont

        visible: true

        Component.onCompleted: {
            default_button_text.load()
        }
    }

    BitmapText {
        id: entered_button_text
        anchors.fill: parent

        text: button.enteredText
        font: button.enteredTextFont

        visible: false

        Component.onCompleted: {
            entered_button_text.load()
        }
    }

    MouseArea {
        id: button_mouse_area
        anchors.fill: button
        onClicked: button.buttonClicked()
        onDoubleClicked: button.buttonDoubleClicked()
        onEntered: {
            default_button_text.visible = false;
            entered_button_text.visible = true;
            button.buttonEntered();
        }
        onExited: {
            default_button_text.visible = true;
            entered_button_text.visible = false;
            button.buttonExited();
        }
    }
}
