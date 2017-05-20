import QtQuick 1.1
import QtD1 1.0

Rectangle {
    id: image

    property int numFrames: 0
    property int startFrame: 0
    property int endFrame: 0
    property int animDuration: 0  // milliseconds
    property real animFPS: 0
    property int current_frame: 0
    property int current_frame_width: 0
    property int current_frame_height: 0
    
    property string source: ""
    property int display: Viewport.NoStretch_AlignSourceCenterWithElementCenter

    // These properties are only used by pcx images
    property int numRows: 1
    property int numCols: 1
    property color transColor: "white"

    signal pcxLoaded
    signal celLoaded
    signal videoLoaded
    signal imageFrameChanged

    // Start the animation
    function startAnimation() {
        image.animDuration = (endFrame-startFrame+1)*50;
        image.animFPS = (endFrame-startFrame+1)*1000.0/animDuration;

        if( cel_image.visible ) {
            cel_image_animation.running = false;
            cel_image_animation.duration = image.animDuration;
            cel_image_animation.from = image.startFrame;
            cel_image_animation.to = image.endFrame;
            cel_image_animation.running = true;
        }
        else if( pcx_image.visible ) {
            pcx_image_animation.running = false;
            pcx_image_animation.duration = image.animDuration;
            pcx_image_animation.from = image.startFrame;
            pcx_image_animation.to = image.endFrame;
            pcx_image_animation.running = true;
        }
        else if( video.visible ) {
            console.log( "video started" );
            video.play();
            console.log( "play loop on new thread" );
        }
        else {
            console.log( "Cannot start animation because no images have been loaded!" );
        }
    }

    // Stop the animation
    function stopAnimation() {
        cel_image_animation.running = false;
        pcx_image_animation.running = false;
        video.stop();
    }

    // Load the animation
    function load() {

        // Stop the animation
        image.stopAnimation()

        // Hide both images and the video
        cel_image.visible = false;
        pcx_image.visible = false;
        video.visible = false;

        // Check the image type
        if( image.source.search( ".cel" ) != -1 || image.source.search( ".cl2" ) != -1) {
            cel_image.source = image.source;
            cel_image.frame = 0;
            cel_image.load();
        }
        else if( image.source.search( ".pcx" ) != -1 ) {
            pcx_image.source = image.source;
            pcx_image.sourceRows = image.numRows;
            pcx_image.sourceCols = image.numCols;
            pcx_image.background = image.transColor;
            pcx_image.frame = 0;
            pcx_image.load();
        }
        else if( image.source.search( ".smk" ) != -1 ) {
            video.source = image.source;
            video.load();
        }
        else {
            console.log( "Image " + image.source + " cannot be displayed!" );
        }
    }

    MenuSprite {
        id: cel_image
        anchors.fill: parent
        displayFrames: "all"
        display: image.display
        visible: false

        onSourceLoaded: {
            cel_image.visible = true;
            image.numFrames = cel_image.numFrames;
            image.current_frame_width = cel_image.frameWidth;
            image.current_frame_height = cel_image.frameHeight;
            image.celLoaded();
        }
        
        onFrameChanged: {
            image.current_frame = cel_image.frame;
            image.current_frame_width = cel_image.frameWidth;
            image.current_frame_height = cel_image.frameHeight;
            imageFrameChanged();
        }

        NumberAnimation on frame {
            id: cel_image_animation
            loops: Animation.Infinite
            duration: image.animDuration
            from: 0
            to: 0
            running: false
        }
    }

    MenuSprite {
        id: pcx_image
        anchors.fill: parent
        display: image.display
        visible: false

        onSourceLoaded: {
            pcx_image.visible = true;
            image.numFrames = pcx_image.numFrames;
            image.current_frame_width = pcx_image.frameWidth;
            image.current_frame_height = pcx_image.frameHeight;
            image.pcxLoaded();
        }

        onFrameChanged: {
            image.current_frame = pcx_image.frame;
            image.current_frame_width = pcx_image.frameWidth;
            image.current_frame_height = pcx_image.frameHeight;
            imageFrameChanged();
        }
        
        NumberAnimation on frame {
            id: pcx_image_animation
            duration: image.animDuration
            loops: Animation.Infinite
            from: 0
            to: 0
            running: false
        }
    }

    Video {
        id: video
        anchors.fill: parent
        //display: image.display
        visible: false

        onSourceLoaded: {
            video.visible = true;
            image.numFrames = 0;
            image.current_frame_width = video.videoWidth;
            image.current_frame_height = video.videoHeight;
            image.videoLoaded();
        }
        onVideoStarted: {
            console.log( "video playing" );
        }
        onVideoFinished: {
            video.visible = false;
        }
    }
}
