import QtQuick 1.1
import QtD1 1.0

/* Component for displaying image of hero */

MenuSprite {
  id: sprite
  width: 225
  height: 95
  source: "/ui_art/heros.pcx"
  background: "#00ff00"
  sourceRows: 4
  startFrame: 3

  Component.onCompleted: {
      sprite.load();
  }
}
