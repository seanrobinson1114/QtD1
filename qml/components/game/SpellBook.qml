import QtQuick 1.1
import QtD1 1.0

/* Component for character spell book */

MenuSprite {
  id: sprite
  width: 320
  height: 352
  source: "/data/spellbk.cel+levels/towndata/town.pal"

  signal openedSpellBook()
  signal closedSpellBook()
  signal openedInventory()
  signal openedCharacterStats()
  signal openedQuestLog()
  signal openedPauseMenu()

  /* Connect custom signals to functions on component completion */
  Component.onCompleted: {
    sprite.loadSync();
    sprite.openedSpellBook.connect(initializeSpellBook);
    sprite.closedSpellBook.connect(closeSpellBook);
  }

  function initializeSpellBook() {
    sprite.showTab( spell_book_tab_1 );
    sprite.hideTabs( [spell_book_tab_2, spell_book_tab_3, spell_book_tab_4] );
  }
  function closeSpellBook() {
    sprite.hideTabs( [spell_book_tab_1, spell_book_tab_2, spell_book_tab_3, spell_book_tab_4] );
  }
  function showTab( tab_id ) {
    tab_id.visible = true;
  }
  function hideTabs( tabs ) {
    for( var i = 0; i < tabs.length; ++i )
      tabs[i].visible = false;
  }

  /* Allow tabs to be opened with key shortcuts */
  Keys.onPressed: {
    if( event.key == Qt.Key_1 ) {
      if( !spell_book_tab_1.visible ) {
        sprite.showTab( spell_book_tab_1 );
        sprite.hideTabs( [spell_book_tab_2, spell_book_tab_3, spell_book_tab_4] );
      }
    }
    else if( event.key == Qt.Key_2 ) {
      if( !spell_book_tab_2.visible ) {
        sprite.showTab( spell_book_tab_2 );
        sprite.hideTabs( [spell_book_tab_1, spell_book_tab_3, spell_book_tab_4] );
      }
    }
    else if( event.key == Qt.Key_3 ) {
      if( !spell_book_tab_3.visible ) {
        sprite.showTab( spell_book_tab_3 );
        sprite.hideTabs( [spell_book_tab_1, spell_book_tab_2, spell_book_tab_4] );
      }
    }
    else if( event.key == Qt.Key_4 ) {
      if( !spell_book_tab_4.visible ) {
        sprite.showTab( spell_book_tab_4 );
        sprite.hideTabs( [spell_book_tab_1, spell_book_tab_2, spell_book_tab_3] );
      }
    }
    else if( event.key == Qt.Key_B ) {
      sprite.closedSpellBook();
    }
    else if( event.key == Qt.Key_I ) {
      sprite.openedInventory();
    }
    else if( event.key == Qt.Key_C ) {
      sprite.openedCharacterStats();
    }
    else if( event.key == Qt.Key_Q ) {
      sprite.openedQuestLog();
    }
    else if( event.key == Qt.Key_Escape ) {
      sprite.openedPauseMenu();
    }
  }

  /* First tab in spell book */
  SpellBookButton {
    id: spell_book_tab_1
    x: 7
    y: 320
    image_frame: 0
    visible: false
  }

  MouseArea {
    id: spell_book_tab_1_ma
    anchors.fill: spell_book_tab_1
    onClicked: {
      if( !spell_book_tab_1.visible ) {
        sprite.showTab( spell_book_tab_1 );
        sprite.hideTabs( [spell_book_tab_2, spell_book_tab_3, spell_book_tab_4] );
      }
    }
  }

  /* Second tab in spell book */
  SpellBookButton {
    id: spell_book_tab_2
    x: spell_book_tab_1.x + 76
    y: spell_book_tab_1.y
    image_frame: 1
    visible: false
  }

  MouseArea {
    id: spell_book_tab_2_ma
    anchors.fill: spell_book_tab_2
    onClicked: {
      if( !spell_book_tab_2.visible ) {
        sprite.showTab( spell_book_tab_2 );
        sprite.hideTabs( [spell_book_tab_1, spell_book_tab_3, spell_book_tab_4] );
      }
    }
  }

  SpellBookButton {
    id: spell_book_tab_3
    x: spell_book_tab_2.x + 77
    y: spell_book_tab_1.y
    image_frame: 2
    visible: false
  }

  /* Third tab in spell book */
  MouseArea {
    id: spell_book_tab_3_ma
    anchors.fill: spell_book_tab_3
    onClicked: {
      if( !spell_book_tab_3.visible ) {
        sprite.showTab( spell_book_tab_3 );
        sprite.hideTabs( [spell_book_tab_1, spell_book_tab_2, spell_book_tab_4] );
      }
    }
  }

  /* Fourth tab in spell book */
  SpellBookButton {
    id: spell_book_tab_4
    x: spell_book_tab_3.x + 76
    y: spell_book_tab_1.y
    image_frame: 3
    visible: false
  }

  MouseArea {
    id: spell_book_tab_4_ma
    anchors.fill: spell_book_tab_4
    onClicked: {
      if( !spell_book_tab_4.visible ) {
        sprite.showTab( spell_book_tab_4 );
        sprite.hideTabs( [spell_book_tab_1, spell_book_tab_2, spell_book_tab_3] );
      }
    }
  }
}
