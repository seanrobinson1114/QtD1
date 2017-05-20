import QtQuick 1.1
import QtD1 1.0
import "components"
import "components/game"

/* Component for options menu */

Rectangle {
  id: options_menu
  width: 800
  height: 600
  color: "transparent"

  Keys.onEscapePressed: {
      game_backend.hideGameOptionsMenu();
  }

    Image {
      id: logo
      width: 296
      height: 100
      anchors.horizontalCenter: parent.horizontalCenter
      source: "/data/diabsmal.cel+levels/towndata/town.pal"
    }

    /* Music */
    OptionsMenuSlider {
      id: music_button
      anchors.top: logo.bottom
      anchors.topMargin: 15
      text: "MUSIC"

      KeyNavigation.up: previous_menu_button
      KeyNavigation.down: sound_button

      onSetVolume: {
        game_backend.setGameMusicVolume( volume );
      }
      onMovedSlider: {
        game_backend.playMenuItemOverSound();
      }
      onHoveredButton: {
        game_backend.playMenuItemOverSound();
      }
      onClickedButton: {
        game_backend.playMenuItemClickSound();
      }
    }

    /* Sound */
    OptionsMenuSlider {
      id: sound_button
      anchors.top: music_button.bottom
      text: "SOUND"

      KeyNavigation.up: music_button
      KeyNavigation.down: gamma_button

      onSetVolume: {
        game_backend.setGameSoundVolume( volume )
      }
      onMovedSlider: {
        game_backend.playMenuItemOverSound();
      }
      onHoveredButton: {
        game_backend.playMenuItemOverSound();
      }
      onClickedButton: {
        game_backend.playMenuItemClickSound();
      }
    }

    /* Gamma */
    BitmapTextButton {
      id: gamma_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: sound_button.bottom
      width: 500
      height: 54
      defaultText: "GAMMA"
      color: "transparent"

      KeyNavigation.up: sound_button
      KeyNavigation.down: color_cycling_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        gamma_button.forceActiveFocus();
      }
      onButtonDoubleClicked: {
        game_backend.playMenuItemClickSound();
      }
      Keys.onUpPressed: {
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          game_backend.playMenuItemOverSound();
          event.accepted = false;
      }
      Keys.onDownPressed: {
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          game_backend.playMenuItemOverSound();
          event.accepted = false;
      }
      Keys.onReturnPressed: {
        game_backend.playMenuItemClickSound();
      }
      Keys.onEscapePressed: {
        gamma_button.focus = false;
        event.accepted = false;
      }

      PentSpin {
          id: gamma_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: gamma_button.focus ? true : false
      }

      PentSpin {
          id: gamma_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: gamma_button.focus ? true : false
      }
    }

    /* Color Cycling */
    BitmapTextButton {
      id: color_cycling_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: gamma_button.bottom
      width: 500
      height: 54
      defaultText: "COLOR CYCLING"
      color: "transparent"

      KeyNavigation.up: gamma_button
      KeyNavigation.down: previous_menu_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        color_cycling_button.forceActiveFocus();
      }
      onButtonDoubleClicked: {
        game_backend.playMenuItemClickSound();
      }
      Keys.onUpPressed: {
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          game_backend.playMenuItemOverSound();
          event.accepted = false;
      }
      Keys.onDownPressed: {
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          game_backend.playMenuItemOverSound();
          event.accepted = false;
      }
      Keys.onReturnPressed: {
        game_backend.playMenuItemClickSound();
      }
      Keys.onEscapePressed: {
        color_cycling_button.focus = false;
        event.accepted = false;
      }

      PentSpin {
          id: color_cycling_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: color_cycling_button.focus ? true : false
      }

      PentSpin {
          id: color_cycling_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: color_cycling_button.focus ? true : false
      }
    }

    /* Previous Menu */
    BitmapTextButton {
      id: previous_menu_button
      anchors.horizontalCenter: logo.horizontalCenter
      anchors.top: color_cycling_button.bottom
      width: 500
      height: 54
      defaultText: "PREVIOUS MENU"
      color: "transparent"

      KeyNavigation.up: color_cycling_button
      KeyNavigation.down: music_button

      onButtonClicked: {
        game_backend.playMenuItemOverSound();
        previous_menu_button.forceActiveFocus();
      }
      Keys.onUpPressed: {
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          game_backend.playMenuItemOverSound();
          event.accepted = false;
      }
      Keys.onDownPressed: {
          // By setting this to false we ensure that the KeyNavigation
          // object will handle this event next
          game_backend.playMenuItemOverSound();
          event.accepted = false;
      }
      Keys.onReturnPressed: {
        previous_menu_button.focus = false;
        game_backend.playMenuItemClickSound();
        game_backend.hideGameOptionsMenu();
      }
      onButtonDoubleClicked: {
        game_backend.playMenuItemClickSound();
        previous_menu_button.focus = false;
        game_backend.hideGameOptionsMenu();
      }
      Keys.onEscapePressed: {
        previous_menu_button.focus = false;
        event.accepted = false;
      }

      PentSpin {
          id: previous_menu_ls
          anchors.left: parent.left
          anchors.verticalCenter: parent.verticalCenter
          anchors.leftMargin: 0
          visible: previous_menu_button.focus ? true : false
      }

      PentSpin {
          id: previous_menu_rs
          anchors.right: parent.right
          anchors.verticalCenter: parent.verticalCenter
          anchors.rightMargin: 0
          visible: previous_menu_button.focus ? true : false
      }
    }

    GameBackend {
        id: game_backend

        onWidgetActivated: {
          music_button.forceActiveFocus();
        }
    }
 }
