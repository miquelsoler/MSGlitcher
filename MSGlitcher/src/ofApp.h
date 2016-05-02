#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "MSGlitcher.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyReleased(int key);

private:

    void onVideoButtonEvent(ofxDatGuiButtonEvent e);
    void onGlitchesButtonEvent(ofxDatGuiButtonEvent e);

    void setGUIPosition();
    void setViewports();
    void updateGlitchesGUI(MSGlitchType selectedGlitchType);

    ofVideoPlayer videoPlayer;
    float videoAspectRatio;
    int viewportWidth, viewportHeight;

    ofxDatGui *guiVideo;
    ofxDatGui *guiGlitches;
    ofxDatGuiToggle *guiGlitchesRed;
    ofxDatGuiToggle *guiGlitchesGreen;
    ofxDatGuiToggle *guiGlitchesBlue;
    ofxDatGui *guiGlitchStack;
};
