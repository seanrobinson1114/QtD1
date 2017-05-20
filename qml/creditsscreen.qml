import QtQuick 1.1
import QtD1 1.0
import "components"

Rectangle {
    id: credits_screen
    width: 800; height: 600
    focus: true
    
    Keys.onEscapePressed: {
        console.log( "credits esc key pressed" );
        timer.stop();
        ui_backend.playMenuItemClickSound();
        ui_backend.gotoMainMenu();
    }

  Timer {
    id: timer
    interval: 50; running: true; repeat: true
    onTriggered: if( credits_text.y > credits_screen.height - credits_text.height ) {
      credits_text.y -= 1;
    }
  }

  Image {
    id: background_c
    anchors.fill: parent
    source: "/ui_art/credits.pcx"
    fillMode: Image.PreserveAspectCrop
  }

  BitmapText {
    id: credits_text
    font: "QtD1Silver30"
    display: "NoStretch_AlignSourceTopLeftWithElementTopLeft"
    visible: true
    x: 0
    y: 600
    height: 600
    width: 800
    containerWidth: 800
    textBehavior: "NoTextWrap"
    Component.onCompleted: {
        credits_text.load();
    }
    text: "Developers
    Alex Robinson, Sean Robinson"
  }

    UIBackend {
        id: ui_backend

        onScreenActivated: {
            credits_text.x = 0
            credits_text.y = 600
            timer.start();
        }
        onScreenDeactivated: {
            timer.stop();
        }
    }
}
