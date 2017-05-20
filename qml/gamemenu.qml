import QtQuick 1.1
import QtD1 1.0
import "components"

/* Component for menu */

Rectangle {
  id: game_menu
  width: 800
  height: 600
  color: "transparent"

  Keys.onEscapePressed: {
      game_backend.hideGameMenu();
  }

  Image {
    id: logo
    width: 296
    height: 100
    anchors.horizontalCenter: parent.horizontalCenter
    source: "/data/diabsmal.cel+levels/towndata/town.pal"
  }

    /* Save Game */
    BitmapTextButton {
      id: save_game_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: logo.bottom
      anchors.topMargin: 15
      width: 350
      height: 54
      defaultText: "SAVE GAME"
      color: "transparent"

      KeyNavigation.up: quit_qtd1_button
      KeyNavigation.down: options_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        save_game_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          game_backend.playMenuItemClickSound();
      }
      onButtonDoubleClicked: {
          game_backend.playMenuItemClickSound();
      }
      Keys.onEscapePressed: {
        event.accepted = false;
      }

      PentSpin {
          id: save_game_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: save_game_button.focus ? true : false
      }

      PentSpin {
          id: save_game_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: save_game_button.focus ? true : false
      }
    }

    /* Options */
    BitmapTextButton {
      id: options_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: save_game_button.bottom
      width: logo.width
      height: 54
      defaultText: "OPTIONS"
      color: "transparent"

      KeyNavigation.up: save_game_button
      KeyNavigation.down: new_game_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        options_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
        game_backend.playMenuItemClickSound();
        game_backend.showGameOptionsMenu();
      }
      onButtonDoubleClicked: {
        game_backend.playMenuItemClickSound();
        game_backend.showGameOptionsMenu();
      }
      Keys.onEscapePressed: {
          options_button.focus = false;
          event.accepted = false;
      }

      PentSpin {
          id: options_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: options_button.focus ? true : false
      }

      PentSpin {
          id: options_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: options_button.focus ? true : false
      }
    }

    /* New Game */
    BitmapTextButton {
      id: new_game_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: options_button.bottom
      width: 340
      height: 54
      defaultText: "NEW GAME"
      color: "transparent"

      KeyNavigation.up: options_button
      KeyNavigation.down: load_game_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        new_game_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          game_backend.playMenuItemClickSound();
      }
      onButtonDoubleClicked: {
          game_backend.playMenuItemClickSound();
      }
      Keys.onEscapePressed: {
        new_game_button.focus = false;
        event.accepted = false;
      }

      PentSpin {
          id: new_game_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: new_game_button.focus ? true : false
      }

      PentSpin {
          id: new_game_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: new_game_button.focus ? true : false
      }
    }

    /* Load Game */
    BitmapTextButton {
      id: load_game_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: new_game_button.bottom
      width: 360
      height: 54
      defaultText: "LOAD GAME"
      color: "transparent"

      KeyNavigation.up: new_game_button
      KeyNavigation.down: quit_qtd1_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        load_game_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          game_backend.playMenuItemClickSound();
      }
      onButtonDoubleClicked: {
          game_backend.playMenuItemClickSound();
      }
      Keys.onEscapePressed: {
        load_game_button.focus = false;
        event.accepted = false;
      }

      PentSpin {
          id: load_game_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: load_game_button.focus ? true : false
      }

      PentSpin {
          id: load_game_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: load_game_button.focus ? true : false
      }
    }

    /* Quit QtD1 */
    BitmapTextButton {
      id: quit_qtd1_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: load_game_button.bottom
      width: 450
      height: 54
      defaultText: "QUIT QTD1"
      color: "transparent"

      KeyNavigation.up: load_game_button
      KeyNavigation.down: save_game_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        quit_qtd1_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          game_backend.playMenuItemOverSound();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          Qt.quit();
      }
      onButtonDoubleClicked: {
          Qt.quit();
      }
      Keys.onEscapePressed: {
        quit_qtd1_button.focus = false;
        event.accepted = false;
      }

      PentSpin {
          id: quit_qtd1_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: quit_qtd1_button.focus ? true : false
      }

      PentSpin {
          id: quit_qtd1_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: quit_qtd1_button.focus ? true : false
      }
    }

    GameBackend {
        id: game_backend

        onWidgetActivated: {
          save_game_button.forceActiveFocus();
        }
    }
}
