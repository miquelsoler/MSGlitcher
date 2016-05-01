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

    void onButtonEvent(ofxDatGuiButtonEvent e);

    ofVideoGrabber videoGrabber;

    ofxDatGui *guiGlitches;
};
