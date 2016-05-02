#include "ofApp.h"

#include "MSGlitcher.h"

static const int GUI_OFFSET = 10;

static const string     GUI_VIDEO_TITLE = "Video Playback";
static const int        GUI_VIDEO_X = GUI_OFFSET;
static const int        GUI_VIDEO_WIDTH = 100;
static const string     GUI_VIDEO_PLAY = "Play / Pause";
static const string     GUI_VIDEO_STOP = "Stop";

static const string     GUI_GLITCHES_TITLE = "GLITCHES";
static const int        GUI_GLITCHES_X = GUI_VIDEO_X + GUI_VIDEO_WIDTH + GUI_OFFSET;
static const int        GUI_GLITCHES_WIDTH = 300;


//--------------------------------------------------------------
void ofApp::setup()
{
    // Load video

    videoPlayer.load("videos/_sampleVideo.in.mp4");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);

    videoAspectRatio = videoPlayer.getWidth() / videoPlayer.getHeight();
    int videoWidth = (int)videoPlayer.getWidth();
    int videoHeight = (int)videoPlayer.getHeight();
    setupViewports();

    videoPlayer.play();

    // Setup video GUI

    guiVideo = new ofxDatGui(ofxDatGuiAnchor::NO_ANCHOR);
    guiVideo->setWidth(GUI_VIDEO_WIDTH);

    guiVideo->addHeader(GUI_VIDEO_TITLE);
    guiVideo->addBreak();

    guiVideo->addButton(GUI_VIDEO_PLAY);
    guiVideo->addButton(GUI_VIDEO_STOP);
    guiVideo->addBreak();

    guiVideo->addFRM();

    guiVideo->onButtonEvent(this, &ofApp::onVideoButtonEvent);

    // Setup glitches GUI

    guiGlitches = new ofxDatGui(ofxDatGuiAnchor::NO_ANCHOR);
    guiGlitches->setWidth(GUI_GLITCHES_WIDTH);

    guiGlitches->addHeader(GUI_GLITCHES_TITLE);
    guiGlitches->addBreak();

    guiGlitches->addToggle(MSGlitchInvert::getName(), false);
    guiGlitches->addToggle(MSGlitchGrayscale::getName(), false);
    guiGlitches->addToggle(MSGlitchRed::getName(), false);
//    guiGlitches->addMatrix("Matrix", 3, true)->setRadioMode(true);

    guiGlitches->addToggle(MSGlitchGreen::getName(), false);
    guiGlitches->addToggle(MSGlitchBlue::getName(), false);
    guiGlitches->addToggle(MSGlitchNoise::getName(), false);

    guiGlitches->onButtonEvent(this, &ofApp::onGlitchesToggleEvent);

    setupGUIPosition();

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
            setupViewports();
            setupGUIPosition();
            break;
        }
        case 'g': {
            bool guiState = guiGlitches->getVisible();
            guiGlitches->setVisible(!guiState);
            break;
        }
        case ' ': {
            videoPlayer.setPaused(!videoPlayer.isPaused());
            break;
        }
        default: break;
    }
}

void ofApp::onVideoButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is(GUI_VIDEO_PLAY)) {
        videoPlayer.setPaused(!videoPlayer.isPaused());
    } else if (e.target->is(GUI_VIDEO_STOP)) {
        videoPlayer.stop();
    }
}

void ofApp::onGlitchesToggleEvent(ofxDatGuiButtonEvent e)
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

void ofApp::setupGUIPosition()
{
    int y = GUI_OFFSET + (ofGetHeight() / 2);
    guiVideo->setPosition(GUI_OFFSET, y);
    guiGlitches->setPosition(GUI_GLITCHES_X, y);
}

void ofApp::setupViewports()
{
    if (videoAspectRatio >= 1.0f) {
        viewportWidth = ofGetWidth()/2;
        viewportHeight = (int)(viewportWidth / videoAspectRatio);
    } else {
        viewportHeight = ofGetHeight()/2;
        viewportWidth = (int)(viewportHeight / videoAspectRatio);
    }
}
