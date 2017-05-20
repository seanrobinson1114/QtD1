import QtQuick 1.1
import QtD1 1.0

/* Component for creating clicked* versions of buttons on spell book */

MenuSprite {
  id: button_image
  width: 76; height: 29
  source: "/data/spellbkb.cel+levels/towndata/town.pal"
  property int image_frame;
  displayFrames: [image_frame]

  Component.onCompleted: {
      button_image.loadSync();
  }
}
