import QtQuick 1.1
import QtD1 1.0
import "components"
import "components/game"

/* Game control panel widget frontend */

Rectangle {
    id: game
    width: control_panel.width
    height: control_panel.height
    color: "transparent"

    ControlPanel {
        id: control_panel
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        onInventoryButtonEngaged: {
            game_backend.showCharacterInventory();
            game_backend.playControlPanelClickSound();
        }
        onInventoryButtonDisengaged: {
            game_backend.hideCharacterInventory();
        }

        onSpellsButtonEngaged: {
            game_backend.showCharacterSpellBook();
            game_backend.playControlPanelClickSound();
        }
        onSpellsButtonDisengaged: {
            game_backend.hideCharacterSpellBook();
        }

        onCharacterButtonEngaged: {
            game_backend.showCharacterStats();
            game_backend.playControlPanelClickSound();
        }
        onCharacterButtonDisengaged: {
            game_backend.hideCharacterStats();
        }
        onQuestButtonEngaged: {
            game_backend.showQuestLog();
            game_backend.playControlPanelClickSound();
        }
        onQuestButtonDisengaged: {
            game_backend.hideQuestLog();
        }

        onMenuButtonEngaged: {
            game_backend.showGameMenu();
            game_backend.playControlPanelClickSound();
        }
    }

    GameBackend {
        id: game_backend

        /* Catch signal when game menu closes */
        onWidgetDeactivated: {
          control_panel.handleGameMenuClosed();
        }
    }
}
