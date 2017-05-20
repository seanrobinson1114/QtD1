import QtQuick 1.1
import QtD1 1.0

MenuSprite {
    id: sprite
    width: 48
    height: 48
    source: "/data/PentSpin.cel+levels/towndata/town.pal"
    displayFrames: "all"
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
