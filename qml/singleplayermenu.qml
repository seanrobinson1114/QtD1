import QtQuick 1.1
import QtD1 1.0
import "components"
import "components/singleplayer"

Rectangle {
    id: singleplayer_screen
    width: 800; height: 600
    Keys.onEscapePressed: {
        console.log( "single player: esc key pressed" );
        ui_backend.playMenuItemClickSound();
        ui_backend.gotoMainMenu();
    }
    Component.onCompleted: {
        new_hero_button.forceActiveFocus();
    }

    Image {
        id: borders
        anchors.fill: parent
        source: "/ui_art/selhero.pcx"
        fillMode: Image.PreserveAspectCrop
    }

    DiabloBanner {
        id: banner
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: header
        anchors.top: banner.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 475
        height: 40
        color: "black"

        BitmapText {
            id: header_text
            anchors.horizontalCenter: header.horizontalCenter
            width: 475
            height: 42
            font: "QtD1Silver30"
            text: "SINGLE PLAYER CHARACTERS"
            Component.onCompleted: {
                header_text.load()
            }
        }
    }

    HeroPicture {
        id: hero_picture
        x: 37
        y: 264
    }

    Rectangle {
        id: hero_stats
        anchors.top: hero_picture.bottom
        anchors.topMargin: 18
        anchors.left: hero_picture.left
        width: hero_picture.width
        height: 200
        color: "black"

        Rogue {
            id: base_rogue;
        }
        Warrior {
            id: base_warrior;
        }
        Sorcerer {
            id: base_sorcerer;
        }
        function setHeroStats( level, strength, magic, dexterity, vitality ) {
            hero_level_text_value.text = level;
            hero_level_text_value.load();
            hero_strength_text_value.text = strength;
            hero_strength_text_value.load();
            hero_magic_text_value.text = magic;
            hero_magic_text_value.load();
            hero_dexterity_text_value.text = dexterity;
            hero_dexterity_text_value.load();
            hero_vitality_text_value.text = vitality;
            hero_vitality_text_value.load();
        }

        function setWarriorBaseStats() {
            setHeroStats( base_warrior.level, base_warrior.strength, base_warrior.magic, base_warrior.dexterity, base_warrior.vitality );
        }

        function setRogueBaseStats() {
            setHeroStats( base_rogue.level, base_rogue.strength, base_rogue.magic, base_rogue.dexterity, base_rogue.vitality );
        }

        function setSorcererBaseStats() {
            setHeroStats( base_sorcerer.level, base_sorcerer.strength, base_sorcerer.magic, base_sorcerer.dexterity, base_sorcerer.vitality );
        }

        // Clears the Stats when cancel is selected on new character selection
        function clearBaseStats() {
            setHeroStats( "-", "-", "-", "-", "-" );
        }

        Rectangle {
            id: hero_level
            anchors.top: hero_stats.top
            anchors.left: hero_stats.left
            width: hero_stats.width
            height: 50
            color: "black"

            BitmapText {
                id: hero_level_text_label
                anchors.right: hero_level.right
                anchors.rightMargin: 57
                anchors.top: hero_level.top
                anchors.topMargin: 27
                width: 100
                height: 16
                font: "QtD1Silver16"
                text: "LEVEL:"
                Component.onCompleted: {
                    hero_level_text_label.load()
            }
        }

            BitmapText {
                id: hero_level_text_value
                anchors.top: hero_level.top
                anchors.topMargin: 27
                anchors.right: hero_level.right
                anchors.rightMargin: 35
                width: 30
                height: 16
                font: "QtD1Silver16"
                text: "-"
                Component.onCompleted: {
                    hero_level_text_value.load()
                }
            }
        }

        Rectangle {
            id: hero_strength
            anchors.top: hero_level.bottom
            anchors.topMargin: 13
            anchors.left: hero_stats.left
            width: hero_stats.width
            height: 30
            color: "black"

            BitmapText {
                id: hero_strength_text_label
                anchors.right: hero_strength.right
                anchors.rightMargin: 72
                anchors.verticalCenter: hero_strength.verticalCenter
                width: 100
                height: 16
                font: "QtD1Silver16"
                text: "STRENGTH:"
                Component.onCompleted: {
                    hero_strength_text_label.load()
                }
            }

            BitmapText {
                id: hero_strength_text_value
                anchors.verticalCenter: hero_strength.verticalCenter
                anchors.right: hero_strength.right
                anchors.rightMargin: 35
                width: 30
                height: 16
                font: "QtD1Silver16"
                text: "-"
                Component.onCompleted: {
                    hero_strength_text_value.load()
                }
            }
        }

        Rectangle {
            id: hero_magic
            anchors.top: hero_strength.bottom
            anchors.left: hero_stats.left
            width: hero_stats.width
            height: 30
            color: "black"

            BitmapText {
                id: hero_magic_text_label
                anchors.right: hero_magic.right
                anchors.rightMargin: 58
                anchors.verticalCenter: hero_magic.verticalCenter
                width: 100
                height: 16
                font: "QtD1Silver16"
                text: "MAGIC:"
                Component.onCompleted: {
                    hero_magic_text_label.load()
                }
            }

            BitmapText {
                id: hero_magic_text_value
                anchors.verticalCenter: hero_magic.verticalCenter
                anchors.right: hero_magic.right
                anchors.rightMargin: 35
                width: 30
                height: 16
                font: "QtD1Silver16"
                text: "-"
                Component.onCompleted: {
                    hero_magic_text_value.load()
                }
            }
        }

        Rectangle {
            id: hero_dexterity
            anchors.top: hero_magic.bottom
            anchors.left: hero_stats.left
            width: hero_stats.width
            height: 30
            color: "black"

            BitmapText {
                id: hero_dexterity_text_label
                anchors.right: hero_dexterity.right
                anchors.rightMargin: 77
                anchors.verticalCenter: hero_dexterity.verticalCenter
                width: 100
                height: 16
                font: "QtD1Silver16"
                text: "DEXTERITY:"
                Component.onCompleted: {
                    hero_dexterity_text_label.load()
                }
            }

            BitmapText {
                id: hero_dexterity_text_value
                anchors.verticalCenter: hero_dexterity.verticalCenter
                anchors.right: hero_dexterity.right
                anchors.rightMargin: 35
                width: 30
                height: 16
                font: "QtD1Silver16"
                text: "-"
                Component.onCompleted: {
                    hero_dexterity_text_value.load()
                }
            }
        }

        Rectangle {
            id: hero_vitality
            anchors.top: hero_dexterity.bottom
            anchors.left: hero_stats.left
            width: hero_stats.width
            height: 30
            color: "black"

            BitmapText {
                id: hero_vitality_text_label
                anchors.right: hero_vitality.right
                anchors.rightMargin: 72
                anchors.verticalCenter: hero_vitality.verticalCenter
                width: 100
                height: 16
                font: "QtD1Silver16"
                text: "VITALITY:"
                Component.onCompleted: {
                    hero_vitality_text_label.load()
                }
            }

            BitmapText {
                id: hero_vitality_text_value
                anchors.verticalCenter: hero_vitality.verticalCenter
                anchors.right: hero_vitality.right
                anchors.rightMargin: 35
                width: 30
                height: 16
                font: "QtD1Silver16"
                text: "-"
                Component.onCompleted: {
                    hero_vitality_text_value.load()
                }
            }
        }
    }

    Rectangle {
        id: commands
        anchors.top: header.bottom
        anchors.topMargin: 9
        anchors.left: hero_picture.right
        anchors.leftMargin: 39
        width: 460
        height: 39
        color: "black"

        BitmapText {
            id: command_text
            anchors.horizontalCenter: commands.horizontalCenter
            anchors.verticalCenter: commands.verticalCenter
            width: 460
            height: 30
            font: "QtD1Silver30"
            text: "SELECT HERO"
            Component.onCompleted: {
                command_text.load()
            }
        }
    }

    Rectangle {
        id: hero_select
        anchors.top: commands.bottom
        anchors.topMargin: 3
        anchors.left: commands.left
        width: commands.width
        height: 218
        color: "black"

        function setAllHeroes() {
            hero_picture.frame = 3;
        }

        function setWarriorHero() {
            hero_picture.frame = 0;
        }
        function isWarriorSelected() {
            if( hero_picture.frame == 0 ) {
                return true;
            }
            else {
                return false;
            }
        }

        function setRogueHero() {
            hero_picture.frame = 1;
        }
        function isRogueSelected() {
            if( hero_picture.frame == 1 ) {
                return true;
            }
            else {
                return false;
            }
        }

        function setSorcererHero() {
            hero_picture.frame = 2;
        }
        function isSorcererSelected() {
            if( hero_picture.frame == 2 ) {
                return true;
            }
            else {
                return false;
            }
        }

        function showHeroOptions() {
            warrior_class_button.visible = false;
            rogue_class_button.visible = false;
            sorcerer_class_button.visible = false;
            new_hero_button.visible = true;
            new_hero_button.forceActiveFocus();
            hero_select.setAllHeroes();
            header_text.text = "SINGLE PLAYER CHARACTERS";
            header_text.load();
            command_text.text = "SELECT HERO";
            command_text.load();
        }
        function showNewHeroClasses() {
            new_hero_button.visible = false;
            header_text.text = "NEW SINGLE PLAYER HERO";
            header_text.load();
            command_text.text = "CHOOSE CLASS";
            command_text.load();
            warrior_class_button.visible = true;
            warrior_class_button.forceActiveFocus();
            hero_select.setWarriorHero();
            rogue_class_button.visible = true;
            sorcerer_class_button.visible = true;
            character_name.visible = false;
        }
        function showNameInputBox() {
            command_text.text = "ENTER NAME";
            command_text.load();
            warrior_class_button.visible = false;
            rogue_class_button.visible = false;
            sorcerer_class_button.visible = false;
            character_name.visible = true;
            character_name.forceActiveFocus();
            character_name.focusOnInput();
        }
        function startGame() {
            ui_backend.stopMenuMusic();

            if( hero_select.isRogueSelected() ) {
                ui_backend.gotoGame( character_name_input.text, Character.Rogue );
            }
            else if( hero_select.isSorcererSelected() ) {
                ui_backend.gotoGame( character_name_input.text, Character.Sorcerer );
            }
            else if( hero_select.isWarriorSelected() ) {
                ui_backend.gotoGame( character_name_input.text, Character.Warrior );
            }
            else {
                console.log( "No character type has been selected!" );
            }
        }

        BitmapTextButton {
            id: new_hero_button
            anchors.top: hero_select.top
            anchors.topMargin: 10
            width: hero_select.width
            height: 25
            color: "black"

            defaultText: "NEW HERO"
            defaultTextFont: "QtD1Gold24"

            function newHeroClicked() {
                ui_backend.playMenuItemClickSound();
                hero_select.showNewHeroClasses();
                hero_select.setWarriorHero();
                hero_stats.setHeroStats( base_warrior.level, base_warrior.strength, base_warrior.magic, base_warrior.dexterity, base_warrior.vitality );
            }

            Keys.onReturnPressed: {
                new_hero_button.newHeroClicked();
            }
            onButtonDoubleClicked: {
                new_hero_button.newHeroClicked();
            }

            SmallPentSpin {
                id: new_hero_ls
                anchors.left: new_hero_button.left
                anchors.verticalCenter: new_hero_button.verticalCenter
                anchors.leftMargin: 30
                visible: new_hero_button.focus ? true : false
            }

            SmallPentSpin {
                id: new_hero_rs
                anchors.right: new_hero_button.right
                anchors.verticalCenter: new_hero_button.verticalCenter
                anchors.rightMargin: 30
                visible: new_hero_button.focus ? true : false
            }
        }

        BitmapTextButton {
            id: warrior_class_button
            anchors.bottom: rogue_class_button.top
            anchors.bottomMargin: 15
            width: hero_select.width
            height: 25
            color: "black"
            visible: false

            defaultText: "WARRIOR"
            defaultTextFont: "QtD1Gold24"

            KeyNavigation.up: sorcerer_class_button
            KeyNavigation.down: rogue_class_button

            Keys.onUpPressed: {
                ui_backend.playMenuItemOverSound();
                hero_select.setSorcererHero();
                hero_stats.setSorcererBaseStats();
                event.accepted = false;
            }
            Keys.onDownPressed: {
                ui_backend.playMenuItemOverSound();
                hero_select.setRogueHero();
                hero_stats.setRogueBaseStats();
                event.accepted = false;
            }
            Keys.onReturnPressed: {
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }
            Keys.onEscapePressed: {
                ui_backend.playMenuItemClickSound();
                hero_stats.clearBaseStats();
                hero_select.showHeroOptions();
            }
            onButtonClicked: {
                ui_backend.playMenuItemOverSound();
                warrior_class_button.forceActiveFocus();
                hero_select.setWarriorHero();
                hero_stats.setWarriorBaseStats();
                console.log( "warrior_class: entered mouse area" );
            }
            onButtonDoubleClicked: {
                console.log( "warrior_class: mouse click" );
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }

            SmallPentSpin {
                id: warrior_class_ls
                anchors.left: warrior_class_button.left
                anchors.verticalCenter: warrior_class_button.verticalCenter
                anchors.leftMargin: 30
                visible: warrior_class_button.focus ? true : false
            }

            SmallPentSpin {
                id: warrior_class_rs
                anchors.right: warrior_class_button.right
                anchors.verticalCenter: warrior_class_button.verticalCenter
                anchors.rightMargin: 30
                visible: warrior_class_button.focus ? true : false
            }
        }

        BitmapTextButton {
            id: rogue_class_button
            anchors.verticalCenter: hero_select.verticalCenter
            anchors.horizontalCenter: hero_select.horizontalCenter
            width: hero_select.width
            height: 25
            color: "black"
            visible: false

            defaultText: "ROGUE"
            defaultTextFont: "QtD1Gold24"

            KeyNavigation.up: warrior_class_button
            KeyNavigation.down: sorcerer_class_button

            Keys.onUpPressed: {
                ui_backend.playMenuItemOverSound();
                hero_select.setWarriorHero();
                hero_stats.setWarriorBaseStats();
                event.accepted = false;
            }
            Keys.onDownPressed: {
                ui_backend.playMenuItemOverSound();
                hero_select.setSorcererHero();
                hero_stats.setSorcererBaseStats();
                event.accepted = false;
            }
            Keys.onReturnPressed: {
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }
            Keys.onEscapePressed: {
                ui_backend.playMenuItemClickSound();
                hero_stats.clearBaseStats();
                hero_select.showHeroOptions();
            }
            onButtonClicked: {
                ui_backend.playMenuItemOverSound();
                rogue_class_button.forceActiveFocus();
                hero_select.setRogueHero();
                hero_stats.setRogueBaseStats();
                console.log( "rogue_class: entered mouse area" );
            }
            onButtonDoubleClicked: {
                console.log( "rogue_class: mouse click" );
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }

            SmallPentSpin {
                id: rogue_class_ls
                anchors.left: rogue_class_button.left
                anchors.verticalCenter: rogue_class_button.verticalCenter
                anchors.leftMargin: 30
                visible: rogue_class_button.focus ? true : false
            }

            SmallPentSpin {
                id: rogue_class_rs
                anchors.right: rogue_class_button.right
                anchors.verticalCenter: rogue_class_button.verticalCenter
                anchors.rightMargin: 30
                visible: rogue_class_button.focus ? true : false
            }
        }

        BitmapTextButton {
            id: sorcerer_class_button
            anchors.top: rogue_class_button.bottom
            anchors.topMargin: 15
            width: hero_select.width
            height: 25
            color: "black"
            visible: false

            defaultText: "SORCERER"
            defaultTextFont: "QtD1Gold24"

            KeyNavigation.up: rogue_class_button
            KeyNavigation.down: warrior_class_button

            Keys.onUpPressed: {
                ui_backend.playMenuItemOverSound();
                hero_select.setRogueHero();
                hero_stats.setRogueBaseStats();
                event.accepted = false;
            }
            Keys.onDownPressed: {
                ui_backend.playMenuItemOverSound();
                hero_select.setWarriorHero();
                hero_stats.setWarriorBaseStats();
                event.accepted = false;
            }
            Keys.onReturnPressed: {
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }
            Keys.onEscapePressed: {
                ui_backend.playMenuItemClickSound();
                hero_stats.clearBaseStats();
                hero_select.showHeroOptions();
            }
            onButtonClicked: {
                ui_backend.playMenuItemOverSound();
                sorcerer_class_button.forceActiveFocus();
                hero_select.setSorcererHero();
                hero_stats.setSorcererBaseStats();
                console.log( "sorcerer_class: entered mouse area" );
            }
            onButtonDoubleClicked: {
                console.log( "sorcerer_class: mouse click" );
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }

            SmallPentSpin {
                id: sorcerer_class_ls
                anchors.left: sorcerer_class_button.left
                anchors.verticalCenter: sorcerer_class_button.verticalCenter
                anchors.leftMargin: 30
                visible: sorcerer_class_button.focus ? true : false
            }

            SmallPentSpin {
                id: sorcerer_class_rs
                anchors.right: sorcerer_class_button.right
                anchors.verticalCenter: sorcerer_class_button.verticalCenter
                anchors.rightMargin: 30
                visible: sorcerer_class_button.focus ? true : false
            }
        }

        Rectangle {
            id: character_name
            anchors.verticalCenter: hero_select.verticalCenter
            anchors.horizontalCenter: hero_select.horizontalCenter
            width: hero_select.width
            height: 25
            color: "black"
            visible: false
            Keys.onReturnPressed: {
                // Make sure the character name has at least one isn't null
                if( character_name_input.text.length > 0 ) {
                    ui_backend.playMenuItemClickSound();
                    hero_select.startGame();
                }
            }
            Keys.onEscapePressed: {
                ui_backend.playMenuItemClickSound();
                hero_select.showNewHeroClasses();
            }
            function focusOnInput() {
                character_name_input.forceActiveFocus();
            }

            SmallPentSpin {
                id: character_name_ls
                anchors.left: character_name.left
                anchors.verticalCenter: character_name.verticalCenter
                anchors.leftMargin: 30
                visible: character_name_input.focus ? true : false
            }

            TextInput {
                id: character_name_input
                autoScroll: true
                anchors.horizontalCenter: character_name.horizontalCenter
                anchors.verticalCenter: character_name.verticalCenter
                color: "silver"
                font.pointSize: 16
                maximumLength: 12
            }

            SmallPentSpin {
                id: character_name_rs
                anchors.right: character_name.right
                anchors.verticalCenter: character_name.verticalCenter
                anchors.rightMargin: 30
                visible: character_name_input.focus ? true : false
            }
        }
    }

    BitmapTextButton {
        id: ok_button
        anchors.top: hero_select.bottom
        anchors.topMargin: 5
        anchors.left: hero_select.left
        anchors.leftMargin: 100
        width: 90
        height: 50
        color: "black"

        defaultText: "OK"
        defaultTextFont: "QtD1Gold30"

        onButtonClicked: {
            if( new_hero_button.activeFocus ) {
                new_hero_button.newHeroClicked();
            }
            else if( warrior_class_button.activeFocus | rogue_class_button.activeFocus | sorcerer_class_button.activeFocus ) {
                ui_backend.playMenuItemClickSound();
                hero_select.showNameInputBox();
            }
            else if( character_name.visible == true ) {
                if( character_name_input.text.length > 0 ) {
                    ui_backend.playMenuItemClickSound();
                    hero_select.startGame();
                }              
            }
        }
    }

    // Rectangle {
    //     id: dlete
    //     anchors.top: hero_select.bottom
    //     anchors.topMargin: 5
    //     anchors.horizontalCenter: hero_select.horizontalCenter
    //     width: 90
    //     height: 50
    //     color: "black"

    //     BitmapText {
    //         id: dlete_text
    //         anchors.horizontalCenter: dlete.horizontalCenter
    //         anchors.verticalCenter: dlete.verticalCenter
    //         width: 60
    //         height: 30
    //         font: "QtD1Gold30"
    //         text: "DELETE"
    //         Component.onCompleted: {
    //             dlete_text.load()
    //         }
    //     }
    // }

    BitmapTextButton {
        id: cancel_button
        anchors.top: hero_select.bottom
        anchors.topMargin: 5
        anchors.right: hero_select.right
        anchors.rightMargin: 90
        width: 110
        height: 50
        color: "black"

        defaultText: "CANCEL"
        defaultTextFont: "QtD1Gold30"

        onButtonClicked: {
            if( new_hero_button.activeFocus ) {
                ui_backend.playMenuItemClickSound();
                ui_backend.gotoMainMenu();
            }
            else if( warrior_class_button.activeFocus | rogue_class_button.activeFocus | sorcerer_class_button.activeFocus ) {
                ui_backend.playMenuItemClickSound();
                hero_stats.clearBaseStats();
                hero_select.showHeroOptions();

            }
            else if( character_name.visible == true ) {
                ui_backend.playMenuItemClickSound();
                hero_select.showNewHeroClasses();
            }
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
