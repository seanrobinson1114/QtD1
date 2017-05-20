import QtQuick 1.1
import QtD1 1.0
import "../"

/* Mouse area with text and slider */
MouseArea {
  id: main_button
  width: 750
  height: 54
  property string text: "NOT SET"
  signal setVolume( int volume );
  signal movedSlider();
  signal hoveredButton();
  signal clickedButton();

  onClicked: {
    main_button.hoveredButton();
    main_button.forceActiveFocus();
  }
  Keys.onUpPressed: {
      // By setting this to false we ensure that the KeyNavigation
      // object will handle this event next
      main_button.hoveredButton();
      event.accepted = false;
  }
  Keys.onDownPressed: {
      //ui_backend.playMenuItemOverSound();
      // By setting this to false we ensure that the KeyNavigation
      // object will handle this event next
      main_button.hoveredButton();
      event.accepted = false;
  }
  Keys.onEscapePressed: {
    main_button.focus = false;
    event.accepted = false;
  }
  Keys.onRightPressed: {
    main_button_slider.moveSlider( main_button_slider.x + 10 );
  }

  Keys.onLeftPressed: {
    main_button_slider.moveSlider( main_button_slider.x - 10 );
  }

  BitmapTextButton {
    id: main_button_text
    anchors.left: parent.left
    width: 300
    height: parent.height
    defaultText: main_button.text
    color: "transparent"

    onButtonClicked: {
      main_button.hoveredButton();
      main_button.forceActiveFocus();
    }
  }

  Image {
    id: main_button_bar
    width: 350
    height: 32
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: parent.right
    anchors.rightMargin: 80
    source: "/data/optbar.cel+levels/towndata/town.pal"

    MouseArea {
      id: main_button_bar_ma
      anchors.fill: parent
      drag {
        target: main_button_slider
        axis: Drag.XAxis
        minimumX: main_button_bar.x
        maximumX: 642
      }

      onPositionChanged: {
        main_button_slider.moveSlider( main_button_bar_ma.mouseX + main_button_bar.x - main_button_slider.width/2 - 5.5 );
      }

      onClicked: {
        main_button_slider.moveSlider( main_button_bar_ma.mouseX + main_button_bar.x - main_button_slider.width/2 - 5.5 );
        main_button.forceActiveFocus();
      }
    }

    Rectangle {
      id: main_filled_area
      width: 335
      height: parent.height - 4
      anchors.left: parent.left
      anchors.leftMargin: 2
      anchors.verticalCenter: parent.verticalCenter
      color: "Maroon"
    }
  }

  Image {
    id: main_button_slider
    width: 27
    height: 28
    anchors.verticalCenter: parent.verticalCenter
    //x: main_button_bar.x
    x: 642
    source: "/data/option.cel+levels/towndata/town.pal"

    function moveSlider( x_location ) {
      if( x_location >= 320 && x_location <= 642 ) {
        main_button_slider.x = x_location;
        main_button.setVolume( ( x_location - 320 ) * 100 / 322 );
      }
    }

    onXChanged: {
      main_filled_area.width = main_button_slider.x - 307;
      if( !main_button_bar_ma.drag.active )
        main_button.movedSlider();
    }
  }

  PentSpin {
      id: main_ls
      anchors.left: parent.left
      anchors.verticalCenter: parent.verticalCenter
      anchors.leftMargin: 0
      visible: main_button.focus ? true : false
  }

  PentSpin {
      id: main_rs
      anchors.right: parent.right
      anchors.verticalCenter: parent.verticalCenter
      anchors.rightMargin: 0
      visible: main_button.focus ? true : false
  }
}
