import QtQuick 1.1
import QtD1 1.0

/* Component for character control panel at bottom */

Image {
    id: control_panel
    width: 640
    height: 144
    source: "/ctrlpan/panel8.cel+levels/towndata/town.pal"
    focus: true

    signal inventoryButtonEngaged
    signal inventoryButtonDisengaged
    signal spellsButtonEngaged
    signal spellsButtonDisengaged
    signal characterButtonEngaged
    signal characterButtonDisengaged
    signal questButtonEngaged
    signal questButtonDisengaged
    signal menuButtonEngaged
    signal menuButtonDisengaged

    function handleGameMenuClosed() {
      menu_button.toggle();
    }

    /* Allow menus to be opened with key shortcuts */
    Keys.onPressed: {
        if( event.key == Qt.Key_I ) {
            event.accepted = true;
            inventory_button.toggle();
        }
        else if( event.key == Qt.Key_B ) {
            event.accepted = true;
            spells_button.toggle();
        }
        else if( event.key == Qt.Key_C ) {
            event.accepted = true;
            character_button.toggle();
        }
        else if( event.key == Qt.Key_Q ) {
            event.accepted = true;
            quest_button.toggle();
        }
        else if( event.key == Qt.Key_Escape ) {
            event.accepted = true;
            menu_button.toggle();
        }
    }

    /* The inventory button */
    ControlPanelButton{
        id: inventory_button
        x: 560
        y: 25

        Component.onCompleted: {
            inventory_button.initInventoryButton();
        }
        onButtonEngaged: {
            if( spells_button.engaged ) {
                spells_button.toggle();
            }
            else if( menu_button.engaged ) {
                menu_button.toggle();
            }
            control_panel.inventoryButtonEngaged();
        }
        onButtonDisengaged: {
            control_panel.inventoryButtonDisengaged();
        }
    }

    /* The spells button */
    ControlPanelButton {
        id: spells_button
        anchors.right: inventory_button.right
        y: inventory_button.y + 26

        Component.onCompleted: {
            spells_button.initSpellsButton();
        }
        onButtonEngaged: {
            if( inventory_button.engaged ) {
                inventory_button.toggle();
            }
            else if( menu_button.engaged ) {
                menu_button.toggle();
            }
            control_panel.spellsButtonEngaged();
        }
        onButtonDisengaged: {
            control_panel.spellsButtonDisengaged();
        }
    }

    /* The char button */
    ControlPanelButton {
        id: character_button
        x: 9
        y: inventory_button.y

        Component.onCompleted: {
            character_button.initCharacterButton();
        }
        onButtonEngaged: {
            if( quest_button.engaged ) {
                quest_button.toggle();
            }
            else if( menu_button.engaged ) {
                menu_button.toggle();
            }
            control_panel.characterButtonEngaged();
        }
        onButtonDisengaged: {
            control_panel.characterButtonDisengaged();
        }
    }

    /* The quest button */
    ControlPanelButton {
        id: quest_button
        x: character_button.x
        y: spells_button.y

        Component.onCompleted: {
            quest_button.initQuestButton();
        }
        onButtonEngaged: {
            if( character_button.engaged ) {
                character_button.toggle();
            }
            else if( menu_button.engaged ) {
                menu_button.toggle();
            }
            control_panel.questButtonEngaged();
        }
        onButtonDisengaged: {
            control_panel.questButtonDisengaged();
        }
    }

    /* The menu button */
    ControlPanelButton {
        id: menu_button
        x: quest_button.x
        y: quest_button.y + 66

        Component.onCompleted: {
            menu_button.initMenuButton();
        }
        onButtonEngaged: {
            if( character_button.engaged ) {
                character_button.toggle();
            }
            if( quest_button.engaged ) {
                quest_button.toggle();
            }
            if( inventory_button.engaged ) {
                inventory_button.toggle();
            }
            if( spells_button.engaged ) {
                spells_button.toggle();
            }
            control_panel.menuButtonEngaged();
        }
        onButtonDisengaged: {
            control_panel.menuButtonDisengaged();
        }
    }
}
