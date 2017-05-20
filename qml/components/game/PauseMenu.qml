import QtQuick 1.1
import QtD1 1.0
import "../"

/* Component for menu */

Rectangle {
  id: menu_container
  width: 800
  height: 472

  signal buttonHovered()
  signal buttonSelected()
  signal quitGame()
  signal setFocus()
  signal pauseMenuClosed()

  function setFocusToSaveGame() {
    save_game_button.forceActiveFocus();
  }

  Component.onCompleted: {
    sprite.loadSync();
    menu_container.setFocus.connect(setFocusToSaveGame);
  }

  Keys.onEscapePressed: {
    console.log( "hit escape menu container" )
    menu_container.pauseMenuClosed();
  }

  MenuSprite {
    id: sprite
    width: 296
    height: 100
    anchors.horizontalCenter: parent.horizontalCenter
    source: "/data/diabsmal.cel+levels/towndata/town.pal"
  }

    /* Save Game */
    BitmapTextButton {
      id: save_game_button
      anchors.horizontalCenter: sprite.horizontalCenter
      anchors.top: sprite.bottom
      anchors.topMargin: 15
      width: 350
      height: 54
      defaultText: "SAVE GAME"
      color: "transparent"

      KeyNavigation.up: quit_qtd1_button
      KeyNavigation.down: options_button

      onButtonClicked: {
        menu_container.buttonHovered();
        save_game_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          menu_container.buttonSelected();
      }
      onButtonDoubleClicked: {
          menu_container.buttonSelected();
      }
      Keys.onEscapePressed: {
        event.accepted = false;
        console.log( "hit escape" )
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
      anchors.horizontalCenter: sprite.horizontalCenter
      anchors.top: save_game_button.bottom
      width: sprite.width
      height: 54
      defaultText: "OPTIONS"
      color: "transparent"

      KeyNavigation.up: save_game_button
      KeyNavigation.down: new_game_button

      onButtonClicked: {
        menu_container.buttonHovered();
        options_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          menu_container.buttonSelected();
      }
      onButtonDoubleClicked: {
          menu_container.buttonSelected();
      }
      Keys.onEscapePressed: {
        console.log( "hit escape" )
        menu_container.pauseMenuClosed();
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
      anchors.horizontalCenter: sprite.horizontalCenter
      anchors.top: options_button.bottom
      width: 340
      height: 54
      defaultText: "NEW GAME"
      color: "transparent"

      KeyNavigation.up: options_button
      KeyNavigation.down: load_game_button

      onButtonClicked: {
        menu_container.buttonHovered();
        new_game_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          menu_container.buttonSelected();
      }
      onButtonDoubleClicked: {
          menu_container.buttonSelected();
      }
      Keys.onEscapePressed: {
        console.log( "hit escape" )
        menu_container.pauseMenuClosed();
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
      anchors.horizontalCenter: sprite.horizontalCenter
      anchors.top: new_game_button.bottom
      width: 360
      height: 54
      defaultText: "LOAD GAME"
      color: "transparent"

      KeyNavigation.up: new_game_button
      KeyNavigation.down: quit_qtd1_button

      onButtonClicked: {
        menu_container.buttonHovered();
        load_game_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          menu_container.buttonSelected();
      }
      onButtonDoubleClicked: {
          menu_container.buttonSelected();
      }
      Keys.onEscapePressed: {
        console.log( "hit escape" )
        menu_container.pauseMenuClosed();
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
      anchors.horizontalCenter: sprite.horizontalCenter
      anchors.top: load_game_button.bottom
      width: 450
      height: 54
      defaultText: "QUIT QTD1"
      color: "transparent"

      KeyNavigation.up: load_game_button
      KeyNavigation.down: save_game_button

      onButtonClicked: {
        menu_container.buttonHovered();
        quit_qtd1_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onDownPressed: {
          menu_container.buttonHovered();
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          event.accepted = false;
      }
      Keys.onReturnPressed: {
          menu_container.quitGame();
      }
      onButtonDoubleClicked: {
          menu_container.quitGame();
      }
      Keys.onEscapePressed: {
        console.log( "hit escape" )
        menu_container.pauseMenuClosed();
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
}
