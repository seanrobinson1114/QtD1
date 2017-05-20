import QtQuick 1.1
import QtD1 1.0

Rectangle {
    id: button
    height: 16
    color: "transparent"

    property string notSelectedText: "select button"
    //property string notSelectedTextFont: 

    property string selectedText: notSelectedText
    //property string selectedTextFont: 

    property bool isSelected: false

    signal selected
    signal deselected

    MenuSprite {
        id: not_selected_image
        width: parent.height
        height: parent.height
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter;
        source: "/ui_art/radio3.pcx"
        background: "black"
        display: Viewport.NoStretch_AlignSourceCenterWithElementCenter

        visible: true

        Component.onCompleted: {
            not_selected_image.load();
        }
    }

    Text {
        id: not_selected_button_text
        width: parent.width - not_selected_image.width;
        height: parent.height
        anchors.left: not_selected_image.right
        anchors.leftMargin: not_selected_image.width/2;
        anchors.verticalCenter: parent.verticalCenter

        text: button.notSelectedText
        //font.family: button.notSelectedTextFont
        horizontalAlignment: Text.AlignLeft

        visible: true
    }
    
    MenuSprite {
        id: selected_image
        width: parent.height
        height: parent.height
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter;
        source: "/ui_art/radio1.pcx"
        background: "black"
        display: Viewport.NoStretch_AlignSourceCenterWithElementCenter

        visible: false

        Component.onCompleted: {
            selected_image.load();
        }
    }

    Text {
        id: selected_button_text
        width: parent.width - selected_image.width;
        height: parent.height
        anchors.left: selected_image.right
        anchors.leftMargin: not_selected_image.width/2;
        anchors.verticalCenter: parent.verticalCenter;

        text: button.selectedText
        //font.family: button.selectedTextFont
        horizontalAlignment: Text.AlignLeft

        visible: false
    }

    MouseArea {
        id: button_mouse_area
        anchors.fill: button
        onClicked: {
            if( button.isSelected ) {
                button.isSelected = false;
                
                selected_image.visible = false;
                selected_button_text.visible = false;

                not_selected_image.visible = true;
                not_selected_button_text.visible = true;
                
                button.deselected();
            }
            else {
                button.isSelected = true;
                
                not_selected_image.visible = false;
                not_selected_button_text.visible = false;

                selected_image.visible = true;
                selected_button_text.visible = true;
                
                button.selected();
            }
        }
    }
}
