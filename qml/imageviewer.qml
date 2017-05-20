import QtQuick 1.1
import QtD1 1.0
import "components"
import "components/imageviewer"

Rectangle {
    id: window
    width: 800
    height: 600
    color: "grey"
    border.color: "black"
    border.width: 43

    CursorDatabase {
        id: cursor_database
    }

    Rectangle {
        id: left_section
        width: 376
        height: 600
        color: "transparent"
        border.color: "black"
        border.width: 10
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        BitmapTextButton {
            id: load_button
            width: 116
            height: 53
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            color: "black"

            defaultText: "Load"
            defaultTextFont: "QtD1Gold30"
            enteredTextFont: "QtD1Silver30"

            onButtonClicked: {
                ui_backend.playMenuItemClickSound();

                image.source = input.text;
                
                if( stretch_image_button.isSelected ) {
                    image.display = Viewport.StretchToFit;
                }
                else {
                    image.display = Viewport.NoStretch_AlignSourceCenterWithElementCenter;
                }
                
                image.numRows = source_rows_input.text;
                image.numCols = source_cols_input.text;
                image.transColor = source_trans_color_input.text;
                image.load();
                cursor_database.activateGameCursor( CursorDatabase.LoadingGameCursor );
            }
        }
        
        BitmapTextButton {
            id: start_button
            width: 109
            height: 53
            anchors.left: load_button.right
            anchors.top: load_button.top
            color: "black"
            
            defaultText: "Start"
            defaultTextFont: "QtD1Gold30"
            enteredTextFont: "QtD1Silver30"

            onButtonClicked: {
                ui_backend.playMenuItemClickSound();
                
                image.startFrame = source_start_frame_text_box_input.text;
                image.endFrame = source_end_frame_text_box_input.text;
                image.startAnimation();
            }
        }

        FrameNavigationButton {
            id: frame_nav_button
            width: 17
            height: 53
            anchors.left: start_button.right
            anchors.verticalCenter: start_button.verticalCenter
            color: "black"

            onUpButtonClicked: {
                image.stopAnimation();

                if( image.current_frame >= 0 && image.current_frame < image.numFrames - 1 ) {
                    image.startFrame = image.current_frame + 1;
                }
                else if( image.current_frame == image.numFrames - 1 ) {
                    image.startFrame = 0;
                }
                else {
                    image.startFrame = 0;
                }
                
                image.endFrame = image.startFrame;
                image.startAnimation();
            }
            onDownButtonClicked: {
                image.stopAnimation();
                
                if( image.current_frame > 0 && image.current_frame < image.numFrames ) {
                    image.startFrame = image.current_frame - 1;
                }
                else if( image.current_frame == 0 )
                {
                    image.startFrame = image.numFrames - 1;
                }
                else {
                    image.startFrame = 0;
                }
                
                image.endFrame = image.startFrame;
                image.startAnimation();
            }
        }
        
        BitmapTextButton {
            id: stop_button
            width: 108
            height: 53
            anchors.left: frame_nav_button.right
            anchors.top: start_button.top
            color: "black"

            defaultText: "Stop"
            defaultTextFont: "QtD1Gold30"
            enteredTextFont: "QtD1Silver30"
            
            onButtonClicked: {
                ui_backend.playMenuItemClickSound();
                image.stopAnimation();
            }
        }
        
        Rectangle {
            id: menu
            width: 352
            height: 200
            anchors.left: parent.left
            anchors.top: load_button.bottom
            anchors.leftMargin: 20
            anchors.topMargin: 10
            color: "transparent"

            Rectangle {
                id: text_box
                width: 340
                height: 48
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 20
                color: "white"
                border.color: "black"
                border.width: 2
                
                Text {
                    id: text_box_header
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "file path + palette path"
                    font.underline: true
                }
                
                TextInput {
                    id: input
                    anchors.top: text_box_header.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    autoScroll: true
                    text: "/monsters/diablo/diabloa.cl2+levels/towndata/town.pal"
                }
            }
            
            Rectangle {
                id: source_rows_text_box
                width: 60
                height: 48
                anchors.top: text_box.bottom
                anchors.left: text_box.left
                anchors.topMargin: 10
                color: "white"
                border.color: "black"
                border.width: 2
                
                Text {
                    id: source_rows_text_box_header
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "rows"
                    font.underline: true
                }

                TextInput {
                    id: source_rows_input
                    anchors.top: source_rows_text_box_header.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "1"
                }
            }
            
            Rectangle {
                id: source_cols_text_box
                width: 60
                height: 48
                anchors.top: source_rows_text_box.top
                anchors.left: source_rows_text_box.right
                color: "white"
                border.color: "black"
                border.width: 2
                
                Text {
                    id: source_cols_text_box_header
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "cols"
                    font.underline: true
                }

                TextInput {
                    id: source_cols_input
                    anchors.top: source_cols_text_box_header.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "1"
                }
            }

            Rectangle {
                id: source_trans_color_text_box
                width: 100
                height: 48
                anchors.top: source_cols_text_box.top
                anchors.left: source_cols_text_box.right
                color: "white"
                border.color: "black"
                border.width: 2
                
                Text {
                    id: source_trans_color_text_box_header
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "trans color"
                    font.underline: true
                    
                }

                TextInput {
                    id: source_trans_color_input
                    anchors.top: source_trans_color_text_box_header.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "#00ff00"
                }
            }

            Rectangle {
                id: source_start_frame_text_box
                width: 50
                height: 48
                anchors.top: source_trans_color_text_box.top
                anchors.left: source_trans_color_text_box.right
                color: "white"
                border.color: "black"
                border.width: 2

                Text {
                    id: source_start_frame_text_box_header
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "start"                     
                    font.underline: true
                }

                TextInput {
                    id: source_start_frame_text_box_input
                    anchors.top: source_start_frame_text_box_header.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "0"
                }
            }

            Rectangle {
                id: source_end_frame_text_box
                width: 70
                height: 48
                anchors.top: source_start_frame_text_box.top
                anchors.left: source_start_frame_text_box.right
                color: "white"
                border.color: "black"
                border.width: 2

                Text {
                    id: source_end_frame_text_box_header
                    anchors.horizontalCenter: parent.horizontalCenter

                    property int maxEntry: 0
                    
                    text: "end (" + maxEntry + ")"
                    font.underline: true
                }

                TextInput {
                    id: source_end_frame_text_box_input
                    anchors.top: source_end_frame_text_box_header.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "0"
                }
            }

            StandardRadioButton {
                id: stretch_image_button
                width: 300
                anchors.left: source_rows_text_box.left
                anchors.top: source_rows_text_box.bottom
                anchors.topMargin: 10

                notSelectedText: "stretch image to fit"
                selectedText: "stretch image to fit"
            }
        }

        Rectangle {
            id: image_details
            width: 352
            height: 200
            anchors.left: menu.left
            anchors.top: menu.bottom
            color: "transparent"

            BitmapText {
                id: image_details_header
                width: 200
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top

                text: "Image Details"
                font: "QtD1Silver30"

                Component.onCompleted: {
                    image_details_header.load()
                }
            }

            BitmapText {
                id: image_frame_text
                width: 100
                height: 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: image_details_header.bottom

                property int image_frame: 0

                text: "frame: " + image_frame
                font: "QtD1Silver16"
                display: Viewport.NoStretch_AlignSourceCenterLeftWithElementCenterLeft
                
                Component.onCompleted: {
                    image_frame_text.load()
                }
            }

            BitmapText {
                id: image_width_text
                width: 100
                height: 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: image_frame_text.bottom

                property int image_width: 0

                text: "width: " + image_width
                font: "QtD1Silver16"
                display: Viewport.NoStretch_AlignSourceCenterLeftWithElementCenterLeft

                Component.onCompleted: {
                    image_width_text.load()
                }
            }

            BitmapText {
                id: image_height_text
                width: 100
                height: 20
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: image_width_text.bottom

                property int image_height: 0

                text: "height: " + image_height
                font: "QtD1Silver16"
                display: Viewport.NoStretch_AlignSourceCenterLeftWithElementCenterLeft

                Component.onCompleted: {
                    image_height_text.load()
                }
            }
        }
    }

    Rectangle {
        id: right_section
        width: 415
        height: 600
        color: "transparent"
        border.color: "black"
        border.width: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    Rectangle {
        id: br_filler
        width: 255
        height: 97
        color: "black"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    MenuSprite {
        id: background
        anchors.fill: parent
        source: "/ui_art/bnselchn.pcx"
        background: "black"

        Component.onCompleted: {
            background.load();
        }

        DynamicImage {
            id: image
            width: 360
            height: 450
            color: window.color
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 30
            anchors.topMargin: 40

            onPcxLoaded: {
                source_trans_color_text_box.color = source_trans_color_input.text;
                source_end_frame_text_box_header.maxEntry = image.numFrames-1;
                source_start_frame_text_box_input.text = "0";
                source_end_frame_text_box_input.text = "0";
                image_frame_text.image_frame = image.current_frame;
                image_frame_text.load();
                image_width_text.image_width = image.current_frame_width;
                image_width_text.load();
                image_height_text.image_height =image.current_frame_height;
                image_height_text.load();
                cursor_database.resetCursor();
            }
            onCelLoaded: {
                source_trans_color_text_box.color = "white";
                source_end_frame_text_box_header.maxEntry = image.numFrames-1;
                source_start_frame_text_box_input.text = "0";
                source_end_frame_text_box_input.text = "0";
                image_frame_text.image_frame = image.current_frame;
                image_frame_text.load();
                image_width_text.image_width = image.current_frame_width;
                image_width_text.load();
                image_height_text.image_height =image.current_frame_height;
                image_height_text.load();
                cursor_database.resetCursor();
            }
            onVideoLoaded: {
                source_trans_color_text_box.color = "white";
                source_end_frame_text_box_header.maxEntry = -1;
                source_start_frame_text_box_input.text = "-1";
                source_end_frame_text_box_input.text = "-1";
                image_frame_text.image_frame = "-1";
                image_frame_text.load();
                image_width_text.image_width = image.current_frame_width;
                image_width_text.load();
                image_height_text.image_height =image.current_frame_height;
                image_height_text.load();
                cursor_database.resetCursor();
            }
            onImageFrameChanged: {
                image_frame_text.image_frame = image.current_frame;
                image_frame_text.load();
                image_width_text.image_width = image.current_frame_width;
                image_width_text.load();
                image_height_text.image_height = image.current_frame_height;
                image_height_text.load();
            }
        }
        
        VerySmallDiabloBanner {
            id: br_logo
            width: 237
            height: 80
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
        }
    }

    UIBackend {
        id: ui_backend
    }
}
