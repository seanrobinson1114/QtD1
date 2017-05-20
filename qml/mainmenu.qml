import QtQuick 1.1
import QtD1 1.0
import "components"

Rectangle {
    id: mainmenu_screen
    width: 800; height: 600
    Component.onCompleted: {
        single_player_button.forceActiveFocus();
    }

    Image {
        id: background
        anchors.fill: parent
        source: "/ui_art/mainmenu.pcx"
        fillMode: Image.PreserveAspectCrop
    }

    DiabloBanner {
        id: banner
        anchors.horizontalCenter: parent.horizontalCenter
    }

    BitmapTextButton {
        id: single_player_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: banner.bottom
        anchors.topMargin: 35
        width: parent.width
        height: 54
        color: "transparent"

        defaultText: "Single Player"
        defaultTextFont: "QtD1Gold42"

        KeyNavigation.up: exit_qtd1_button
        KeyNavigation.down: multi_player_button

        Keys.onReturnPressed: {
            ui_backend.playMenuItemClickSound();
            ui_backend.gotoSinglePlayerMenu();
        }
        Keys.onUpPressed: {
            ui_backend.playMenuItemOverSound();
            // By setting this to false we ensure that the KeyNavigation
            // object will handle this event next
            event.accepted = false;
        }
        Keys.onDownPressed: {
            ui_backend.playMenuItemOverSound();
            // By setting this to false we ensure that the KeyNavigation
            // object will handle this event next
            event.accepted = false;
        }
        onButtonClicked: {
            ui_backend.playMenuItemOverSound();
            single_player_button.forceActiveFocus();
            console.log( "single_player: entered mouse area" );
        }
        onButtonDoubleClicked: {
            console.log( "single_player: mouse click" );
            ui_backend.playMenuItemClickSound();
            ui_backend.gotoSinglePlayerMenu();
        }

        PentSpin {
            id: single_player_ls
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 90
            visible: single_player_button.focus ? true : false
        }

        PentSpin {
            id: single_player_rs
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 100
            visible: single_player_button.focus ? true : false
        }
    }

    BitmapTextButton {
        id: multi_player_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: single_player_button.bottom
        width: parent.width
        height: 54
        color: "transparent"

        defaultText: "Multi Player"
        defaultTextFont: "QtD1Gold42"

        KeyNavigation.up: single_player_button
        KeyNavigation.down: replay_intro_button

        Keys.onReturnPressed: {
            ui_backend.playMenuItemClickSound();
        }
        Keys.onUpPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        Keys.onDownPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        onButtonClicked: {
            ui_backend.playMenuItemOverSound();
            multi_player_button.forceActiveFocus();
            console.log( "multi_player: entered mouse area" );
        }
        onButtonDoubleClicked: {
            console.log( "multi_player: mouse click" );
            ui_backend.playMenuItemClickSound();
        }

        PentSpin {
            id: multi_player_ls
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 90
            visible: multi_player_button.focus ? true : false
        }

        PentSpin {
            id: multi_player_rs
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 100
            visible: multi_player_button.focus ? true : false
        }
    }

    BitmapTextButton {
        id: replay_intro_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: multi_player_button.bottom
        width: parent.width
        height: 54
        color: "transparent"

        defaultText: "Replay Intro"
        defaultTextFont: "QtD1Gold42"

        KeyNavigation.up: multi_player_button
        KeyNavigation.down: show_credits_button

        Keys.onReturnPressed: {
            ui_backend.playMenuItemClickSound();
            ui_backend.gotoIntroScreen();
        }
        Keys.onUpPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        Keys.onDownPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        onButtonClicked: {
            ui_backend.playMenuItemOverSound();
            replay_intro_button.forceActiveFocus();
            console.log( "replay_intro: entered mouse area" );
        }
        onButtonDoubleClicked: {
            console.log( "replay_intro: mouse click" );
            ui_backend.playMenuItemClickSound();
            ui_backend.gotoIntroScreen();
        }

        PentSpin {
            id: replay_intro_ls
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 90
            visible: replay_intro_button.focus ? true : false
        }

        PentSpin {
            id: replay_intro_rs
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 100
            visible: replay_intro_button.focus ? true : false
        }
    }

    BitmapTextButton {
        id: show_credits_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: replay_intro_button.bottom
        width: parent.width
        height: 54
        color: "transparent"

        defaultText: "Show Credits"
        defaultTextFont: "QtD1Gold42"

        KeyNavigation.up: replay_intro_button
        KeyNavigation.down: exit_qtd1_button

        Keys.onReturnPressed: {
            ui_backend.playMenuItemClickSound();
            //event.accepted = false;
            ui_backend.gotoCreditsScreen();
        }
        Keys.onUpPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        Keys.onDownPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        onButtonClicked: {
            ui_backend.playMenuItemOverSound();
            show_credits_button.forceActiveFocus();
        }
        onButtonDoubleClicked: {
            console.log( "credits: mouse click" );
            ui_backend.playMenuItemClickSound();
            ui_backend.gotoCreditsScreen();
        }

        PentSpin {
            id: credits_ls
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 90
            visible: show_credits_button.focus ? true : false
        }

        PentSpin {
            id: credits_rs
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 100
            visible: show_credits_button.focus ? true : false
        }
    }

    BitmapTextButton {
        id: exit_qtd1_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: show_credits_button.bottom
        width: parent.width
        height: 54
        color: "transparent"

        defaultText: "Exit QtD1"
        defaultTextFont: "QtD1Gold42"

        KeyNavigation.up: show_credits_button
        KeyNavigation.down: single_player_button

        Keys.onReturnPressed: {
            Qt.quit();
        }
        Keys.onUpPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        Keys.onDownPressed: {
            ui_backend.playMenuItemOverSound();
            event.accepted = false;
        }
        onButtonClicked: {
            ui_backend.playMenuItemOverSound();
            exit_qtd1_button.forceActiveFocus();
        }
        onButtonDoubleClicked: {
            console.log( "exit qtd1: mouse click" );
            ui_backend.playMenuItemClickSound();
            Qt.quit();
        }

        PentSpin {
            id: exit_ls
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 90
            visible: exit_qtd1_button.focus ? true : false
        }

        PentSpin {
            id: exit_rs
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 100
            visible: exit_qtd1_button.focus ? true : false
        }
    }

    BitmapText {
        id: version_number
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 80
        anchors.bottomMargin: 40
        width: 100
        height: 16
        text: "QtD1 1.0"
        font: "QtD1Silver16"
        display: Viewport.NoStretch_AlignSourceCenterLeftWithElementCenterLeft
        Component.onCompleted: {
            version_number.load()
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
