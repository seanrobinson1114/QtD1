import QtQuick 1.1
import QtD1 1.0

MenuSprite {
    id: logo_sprite
    width: 260
    height: 102
    source: "/ui_art/xsmlogo.pcx"
    background: "#00ff00"
    sourceRows: 15
    startFrame: 0

    NumberAnimation on frame {
        loops: Animation.Infinite
        duration: 800
        from: 0
        to: 15
    }

    Component.onCompleted: {
        logo_sprite.loadSync();
    }
}
