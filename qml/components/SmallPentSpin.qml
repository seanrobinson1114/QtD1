import QtQuick 1.1
import QtD1 1.0

MenuSprite {
    id: sprite
    width: 25
    height: 25
    source: "/ui_art/focus16.pcx"
    background: "#00ff00"
    sourceRows: 8
    startFrame: 0

    NumberAnimation on frame {
        loops: Animation.Infinite
        duration: 300
        from: 0
        to: 7
    }

    Component.onCompleted: {
        sprite.loadSync();
    }
}
