#include "ofApp.h"

#include "MSGlitcher.h"

static const int GUI_GLITCHES_OFFSET = 10;

//--------------------------------------------------------------
void ofApp::setup()
{
    // Load video

    videoPlayer.load("videos/_sampleVideo.in.mp4");
    videoPlayer.setLoopState(OF_LOOP_PALINDROME);

    videoAspectRatio = videoPlayer.getWidth() / videoPlayer.getHeight();
    int videoWidth = (int)videoPlayer.getWidth();
    int videoHeight = (int)videoPlayer.getHeight();
    updateViewports();

    videoPlayer.play();

    // Setup glitches GUI

    guiGlitches = new ofxDatGui(GUI_GLITCHES_OFFSET, GUI_GLITCHES_OFFSET + ofGetHeight()/2);
    guiGlitches->setWidth(400);

    guiGlitches->addHeader("GLITCHES");
    guiGlitches->addBreak();

    guiGlitches->addFRM();
    guiGlitches->addBreak();

    guiGlitches->addToggle(MSGlitchInvert::getName(), false);
    guiGlitches->addToggle(MSGlitchGrayscale::getName(), false);
    guiGlitches->addToggle(MSGlitchRed::getName(), false);
    guiGlitches->addMatrix("Matrix", 3, true)->setRadioMode(true);

    guiGlitches->addToggle(MSGlitchGreen::getName(), false);
    guiGlitches->addToggle(MSGlitchBlue::getName(), false);
    guiGlitches->addToggle(MSGlitchNoise::getName(), false);

    guiGlitches->onButtonEvent(this, &ofApp::onButtonEvent);

    // Init glitcher

    MSGlitcher::getInstance().init(videoWidth, videoHeight);

    // App setup

    ofSetBackgroundColor(ofColor::black);
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
    videoPlayer.update();

    if (videoPlayer.isFrameNew()) {
        MSGlitcher::getInstance().update(videoPlayer.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    videoPlayer.draw(0, 0, viewportWidth, viewportHeight);
    MSGlitcher::getInstance().draw(ofGetWidth()/2, 0, viewportWidth, viewportHeight);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    MSGlitcher &glitcher = MSGlitcher::getInstance();

    switch(key)
    {
        case 'f':
        case 'F': {
            ofToggleFullscreen();
            updateViewports();
            guiGlitches->setPosition(GUI_GLITCHES_OFFSET, GUI_GLITCHES_OFFSET + ofGetHeight()/2);
            break;
        }
        case 'g': {
            bool guiState = guiGlitches->getVisible();
            guiGlitches->setVisible(!guiState);
            break;
        }
        default: break;
    }
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    bool isEnabled = e.enabled;
    MSGlitchType glitchType;
    MSGlitcher &glitcher = MSGlitcher::getInstance();

    // Get glitch type
    if (e.target->is(MSGlitchInvert::getName())) {
        glitchType = MSGT_INVERT;
    } else if (e.target->is(MSGlitchGrayscale::getName())) {
        glitchType = MSGT_GRAYSCALE;
    } else if (e.target->is(MSGlitchRed::getName())) {
        glitchType = MSGT_RED;
    } else if (e.target->is(MSGlitchGreen::getName())) {
        glitchType = MSGT_GREEN;
    } else if (e.target->is(MSGlitchBlue::getName())) {
        glitchType = MSGT_BLUE;
    } else if (e.target->is(MSGlitchNoise::getName())) {
        glitchType = MSGT_NOISE;
    }

    // Add/remove glitch
    if (isEnabled) {
        glitcher.addGlitch(glitchType);
    } else {
        glitcher.removeGlitch(glitchType);
    }
}

void ofApp::updateViewports()
{
    if (videoAspectRatio >= 1.0f) {
        viewportWidth = ofGetWidth()/2;
        viewportHeight = (int)(viewportWidth / videoAspectRatio);
    } else {
        viewportHeight = ofGetHeight()/2;
        viewportWidth = (int)(viewportHeight / videoAspectRatio);
    }
}
