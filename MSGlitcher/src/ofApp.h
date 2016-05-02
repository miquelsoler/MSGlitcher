#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyReleased(int key);

private:

    void setupGUIPosition();
    void setupViewports();

    void onVideoButtonEvent(ofxDatGuiButtonEvent e);
    void onGlitchesToggleEvent(ofxDatGuiButtonEvent e);

    ofVideoPlayer videoPlayer;
    float videoAspectRatio;
    int viewportWidth, viewportHeight;

    ofxDatGui *guiVideo;
    ofxDatGui *guiGlitches;
};
