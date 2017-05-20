import QtQuick 1.1
import QtD1 1.0
import "components"

Rectangle {
    id: intro_screen
    width: 800; height: 600
    color: "black"
    focus: true
    Keys.onEscapePressed: {
        ui_backend.playMenuItemClickSound();
        intro_screen_video.stop();
        ui_backend.gotoMainMenu();
    }

    Video {
        id: intro_screen_video
        anchors.fill: parent

        source: "/gendata/diablo1.smk"

        onSourceLoaded: {
            intro_screen_video.play();
        }
        onVideoFinished: {
            ui_backend.gotoMainMenu();
        }
    }

    UIBackend {
        id: ui_backend

        onScreenActivated: {
            ui_backend.stopMenuMusic();
            intro_screen_video.load();
        }
    }
}
