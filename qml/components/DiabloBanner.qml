import QtQuick 1.1
import QtD1 1.0

MenuSprite {
    id: logo_sprite
    width: 550
    height: 216
    source: "/ui_art/logo.pcx"
    background: "#00ff00"
    sourceRows: 15
    startFrame: 0

    NumberAnimation on frame {
        id: logo_sprite_animation
        loops: Animation.Infinite
        duration: 800
        from: 0
        to: 14
    }

    Component.onCompleted: {
        logo_sprite.loadSync();
    }
}
