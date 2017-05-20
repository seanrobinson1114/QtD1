import QtQuick 1.1
import QtD1 1.0

/* Component for creating clicked* versions of buttons on control panel */
Rectangle{
    id: button
    width: 71
    height: 19
    color: "transparent"

    signal buttonEngaged
    signal buttonDisengaged

    property bool engaged

    function initCharacterButton() {
        button_image.frame = 0;
        button_image.displayFrames = [0];
        button_image.loadSync();
        button_image.visible = false;
        button.engaged = false;
    }

    function initQuestButton() {
        button_image.frame = 1;
        button_image.loadSync();
        button_image.visible = false;
        button.engaged = false;
    }

    function initMenuButton() {
        button_image.frame = 3;
        button_image.loadSync();
        button_image.visible = false;
        button.engaged = false;
    }

    function initInventoryButton() {
        button_image.frame = 4;
        button_image.loadSync();
        button_image.visible = false;
        button.engaged = false;
    }

    function initSpellsButton() {
        button_image.frame = 5;
        button_image.loadSync();
        button_image.visible = false;
        button.engaged = false;
    }

    function toggle() {
        if( button_image.visible ) {
            button_image.visible = false;
            button.engaged = false;
            button.buttonDisengaged();
        }
        else {
            button_image.visible = true;
            button.engaged = true;
            button.buttonEngaged();
        }
    }

    MenuSprite {
        id: button_image
        anchors.fill: button
        source: "/ctrlpan/panel8bu.cel+levels/towndata/town.pal"
        visible: false
    }

    MouseArea {
        id: button_mouse_area
        anchors.fill: button
        onClicked: {
            button.toggle();
        }
    }
}
