import QtQuick 1.1
import QtD1 1.0

/* Component for character stats */

Rectangle {
    id: character_stats
    width: 320
    height: 352

    function update() {
        level_text.text = character.level;
        experience_text.text = character.experience;
        next_level_experience_text.text = character.nextLevelExperience;
        gold_text.text = character.gold;

        base_strength_text.text = character.baseStrength;
        strength_text.text = character.strength;
        base_magic_text.text = character.baseMagic;
        magic_text.text = character.magic;
        base_dexterity_text.text = character.baseDexterity;
        dexterity_text.text = character.dexterity;
        base_vitality_text.text = character.baseVitality;
        vitality_text.text = character.vitality;

        max_health_text.text = character.maxHealth;
        health_text.text = character.health;
        max_mana_text.text = character.maxMana;
        mana_text.text = character.mana;

        armor_class_text.text = character.armorClass;
        chance_to_hit_text.text = character.chanceToHit + '%';
        damage_text.text = character.minimumDamage + '-' + character.maximumDamage;

        resist_magic_text.text = character.magicResistance + '%';
        resist_fire_text.text = character.fireResistance + '%';
        resist_lightning_text.text = character.lightningResistance + '%';
    }

    Image {
        id: character_stats_background
        anchors.fill: parent
        source: "/data/char.cel+levels/towndata/town.pal"

        Rectangle {
            id: character_name_block
            x: 18
            y: 18
            width: 137
            height: 16
            color: "transparent"

            Text {
                id: character_name_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: character_type_block
            x: 166
            y: 18
            width: 137
            height: 16
            color: "transparent"

            Text {
                id: character_type_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: level_block
            x: 62
            y: 56
            width: 48
            height: 16
            color: "transparent"

            Text {
                id: level_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: experience_block
            x: 213
            y: 56
            width: 90
            height: 16
            color: "transparent"

            Text {
                id: experience_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: next_level_experience_block
            x: 213
            y: 84
            width: 90
            height: 16
            color: "transparent"

            Text {
                id: next_level_experience_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: gold_block
            x: 213
            y: 133
            width: 90
            height: 16
            color: "transparent"

            Text {
                id: gold_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: base_strength_block
            x: 92
            y: 141
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: base_strength_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: strength_block
            x: 140
            y: 141
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: strength_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: base_magic_block
            x: 92
            y: 169
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: base_magic_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: magic_block
            x: 140
            y: 169
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: magic_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: base_dexterity_block
            x: 92
            y: 197
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: base_dexterity_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: dexterity_block
            x: 140
            y: 197
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: dexterity_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: base_vitality_block
            x: 92
            y: 225
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: base_vitality_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: vitality_block
            x: 140
            y: 225
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: vitality_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: points_to_distribute_block
            x: 92
            y: 253
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: points_to_distribution_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: max_health_block
            x: 92
            y: 290
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: max_health_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: health_block
            x: 140
            y: 290
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: health_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: max_mana_block
            x: 92
            y: 318
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: max_mana_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: mana_block
            x: 140
            y: 318
            width: 37
            height: 16
            color: "transparent"

            Text {
                id: mana_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: armor_class_block
            x: 254
            y: 169
            width: 50
            height: 16
            color: "transparent"

            Text {
                id: armor_class_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
        id: chance_to_hit_block
            x: 254
            y: 197
            width: 50
            height: 16
            color: "transparent"

            Text {
                id: chance_to_hit_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: damage_block
            x: 254
            y: 225
            width: 50
            height: 16
            color: "transparent"

            Text {
                id: damage_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: resist_magic_block
            x: 254
            y: 262
            width: 50
            height: 16
            color: "transparent"

            Text {
                id: resist_magic_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: resist_fire_block
            x: 254
            y: 290
            width: 50
            height: 16
            color: "transparent"

            Text {
                id: resist_fire_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }

        Rectangle {
            id: resist_lightning_block
            x: 254
            y: 318
            width: 50
            height: 16
            color: "transparent"

            Text {
                id: resist_lightning_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                color: "white"
                font.family: "FreeMonoBold"
                font.pointSize: 10
            }
        }
    }

    CharacterBackend {
        id: character

        onLevelUp: {
            points_to_distribution_text.text = "5"
        }
        onHealthChanged: {
            health_text.text = current_health;

            if( current_health < character.maxHealth ) {
                health_text.color = "pink"
            }
        }
        onManaChanged: {
            mana_text.text = current_mana;

            if( current_mana < character.maxMana ) {
                mana_text.color = "pink"
            }
        }
        onStatsChanged: {
            character_stats.update();
        }
    }
    
    GameBackend {
        id: game_backend

        onGameLoadFinished: {
            character_name_text.text = character.name;

            if( character.type == Character.Rogue ) {
                character_type_text.text = "ROGUE";
            }
            else if( character.type == Character.Sorcerer ) {
                character_type_text.text = "SORCERER";
            }
            else if( character.type == Character.Warrior ) {
                character_type_text.text = "WARRIOR";
            }
            else {
                character_type_text.text = "UNKNOWN";
            }

            character_stats.update();
        }
    }
}
