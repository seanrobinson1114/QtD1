import QtQuick 1.1
import QtD1 1.0

Rectangle {
    id: button
    width: 17
    height: 17

    property bool up: true

    signal buttonClicked
    signal buttonEntered
    signal buttonExited

    MenuSprite {
        id: button_image
        anchors.fill: button

        source: "/ui_art/scrlarrw.pcx"
        sourceRows: 4
        display: Viewport.NoStretch_AlignSourceCenterLeftWithElementCenterLeft
        frame: button.up ? 0 : 1;

        Component.onCompleted: {
            button_image.load();
        }
    }

    MouseArea {
        id: button_mouse_area
        anchors.fill: button

        onClicked: button.buttonClicked()
        onEntered: {
            button_image.frame = button.up ? 2 : 3;
            button.buttonEntered();
        }
        onExited: {
            button_image.frame = button.up ? 0 : 1;
            button.buttonExited();
        }
    }
}
