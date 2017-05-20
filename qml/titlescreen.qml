import QtQuick 1.1
import QtD1 1.0
import "components"

Rectangle {
    id: title_screen
    width: 800; height: 600
    color: "black"
    focus: true
    
    Keys.onPressed: {
      if( activeFocus ) {
          ui_backend.playMenuItemClickSound();
          ui_backend.gotoMainMenu();
      }
    }

    Image {
        id: background
        anchors.centerIn: parent
        source: "/ui_art/title.pcx"
        fillMode: Image.PreserveAspectCrop

        DiabloBanner {
            id: banner
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 100
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MouseArea {
        id: titlescreen_ma
        hoverEnabled: true
        anchors.fill: parent
        onClicked: {
            ui_backend.playMenuItemClickSound();
            ui_backend.gotoMainMenu();
        }
        acceptedButtons: {
            Qt.LeftButton
        }
    }

    UIBackend {
        id: ui_backend

        onScreenActivated: {
            if( !ui_backend.menuMusicPlaying ) {
                ui_backend.playMenuMusic();
            }
        }
    }
}
