import QtQuick 1.1
import QtD1 1.0

/* Component for quest log */

MenuSprite {
  id: sprite
  width: 320
  height: 352
  source: "/data/quest.cel+levels/towndata/town.pal"

  Component.onCompleted: {
      sprite.loadSync();
  }
}
