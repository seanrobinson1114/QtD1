import QtQuick 1.1
import QtD1 1.0

/* Component for character inventory */

MenuSprite {
  id: sprite
  width: 320
  height: 352
  source: "/data/inv/inv.cel+levels/towndata/town.pal"

  Component.onCompleted: {
      sprite.loadSync();
  }
}
