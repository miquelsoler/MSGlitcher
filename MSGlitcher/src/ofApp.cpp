#include "ofApp.h"

static const int        GUI_OFFSET = 10;

static const string     GUI_VIDEO_TITLE = "Video Playback";
static const int        GUI_VIDEO_X = GUI_OFFSET;
static const int        GUI_VIDEO_WIDTH = 230;
static const string     GUI_VIDEO_PLAY = "Play / Pause";
static const string     GUI_VIDEO_STOP = "Stop";

static const string     GUI_GLITCHES_TITLE = "GLITCHES";
static const int        GUI_GLITCHES_X = GUI_VIDEO_X + GUI_VIDEO_WIDTH + GUI_OFFSET;
static const int        GUI_GLITCHES_WIDTH = 140;

static const string     GLITCHSTACK_TITLE = "GLITCH STACK:";
static const int        GLITCHSTACK_X = GUI_GLITCHES_X + GUI_GLITCHES_WIDTH + GUI_OFFSET;


//--------------------------------------------------------------
void ofApp::setup()
{
    // Load video

    videoPlayer.load("videos/_sampleVideo.in.mp4");
    videoPlayer.setLoopState(OF_LOOP_NORMAL);

    videoAspectRatio = videoPlayer.getWidth() / videoPlayer.getHeight();
    int videoWidth = (int)videoPlayer.getWidth();
    int videoHeight = (int)videoPlayer.getHeight();
    setViewports();

    videoPlayer.play();

    { // Setup video GUI
        guiVideo = new ofxDatGui(ofxDatGuiAnchor::NO_ANCHOR);
        guiVideo->setTheme(new ofxDatGuiThemeAutumn());
        guiVideo->setWidth(GUI_VIDEO_WIDTH);

        guiVideo->addHeader(GUI_VIDEO_TITLE);
        guiVideo->addBreak();

        guiVideo->addButton(GUI_VIDEO_PLAY);
        guiVideo->addButton(GUI_VIDEO_STOP);
        guiVideo->addBreak();

        guiVideo->addFRM();

        guiVideo->onButtonEvent(this, &ofApp::onVideoButtonEvent);
    }

    { // Setup glitches GUI
        guiGlitches = new ofxDatGui(ofxDatGuiAnchor::NO_ANCHOR);
        guiGlitches->setTheme(new ofxDatGuiThemeAutumn());
        guiGlitches->setWidth(GUI_GLITCHES_WIDTH);

        guiGlitches->addHeader(GUI_GLITCHES_TITLE);
        guiGlitches->addBreak();

        guiGlitches->addToggle(MSGlitchInvert::getName(), false);
        guiGlitches->addToggle(MSGlitchGrayscale::getName(), false);
        guiGlitchesRed = guiGlitches->addToggle(MSGlitchRed::getName(), false);
        guiGlitchesGreen = guiGlitches->addToggle(MSGlitchGreen::getName(), false);
        guiGlitchesBlue = guiGlitches->addToggle(MSGlitchBlue::getName(), false);
        guiGlitches->addToggle(MSGlitchNoise::getName(), false);

        guiGlitches->onButtonEvent(this, &ofApp::onGlitchesButtonEvent);
    }

    showGlitchesStack = true;
    buildGlitchesStackText();

    setGUIPosition();

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

    ofPushStyle();
    {
        int textHeight = 10;
        int textOffset = 10;
        int x = ofGetWidth() - 200;
        int y = ofGetHeight() / 2 + textOffset*2;

        if (showGlitchesStack) {
            ofPushStyle();
            ofSetColor(ofColor::darkGreen);
            ofDrawBitmapString(glitchesStackText.str(), x, y);
            ofPopStyle();
        }
    }
    ofPopStyle();
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
            setViewports();
            setGUIPosition();
            break;
        }
        case 'g': {
            bool guiState = guiGlitches->getVisible();
            guiVideo->setVisible(!guiState);
            guiGlitches->setVisible(!guiState);
            showGlitchesStack = !showGlitchesStack;
            break;
        }
        case ' ': {
            videoPlayer.setPaused(!videoPlayer.isPaused());
            break;
        }
        default: break;
    }
}

void ofApp::setGUIPosition()
{
    int y = GUI_OFFSET + (ofGetHeight() / 2);
    guiVideo->setPosition(GUI_OFFSET, y);
    guiGlitches->setPosition(GUI_GLITCHES_X, y);
}

void ofApp::onVideoButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is(GUI_VIDEO_PLAY)) {
        videoPlayer.setPaused(!videoPlayer.isPaused());
    } else if (e.target->is(GUI_VIDEO_STOP)) {
        videoPlayer.stop();
    }
}

void ofApp::onGlitchesButtonEvent(ofxDatGuiButtonEvent e)
{
    bool isEnabled = e.enabled;
    MSGlitchType glitchType = MSGT_NONE;
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
        updateGlitchesGUI(glitchType);
    } else {
        glitcher.removeGlitch(glitchType);
    }

    MSGlitcher::getInstance().update(videoPlayer.getPixels());

    buildGlitchesStackText();
}

void ofApp::setViewports()
{
    if (videoAspectRatio >= 1.0f) {
        viewportWidth = ofGetWidth()/2;
        viewportHeight = (int)(viewportWidth / videoAspectRatio);
    } else {
        viewportHeight = ofGetHeight()/2;
        viewportWidth = (int)(viewportHeight / videoAspectRatio);
    }
}

void ofApp::updateGlitchesGUI(MSGlitchType selectedGlitchType)
{
    // R, G and B glitches are mutually exclusive
    switch(selectedGlitchType) {
        case MSGT_RED:
            guiGlitchesGreen->setEnabled(false);
            guiGlitchesBlue->setEnabled(false);
            break;
        case MSGT_GREEN:
            guiGlitchesRed->setEnabled(false);
            guiGlitchesBlue->setEnabled(false);
            break;
        case MSGT_BLUE:
            guiGlitchesRed->setEnabled(false);
            guiGlitchesGreen->setEnabled(false);
            break;
        default: break;
    }
}

void ofApp::buildGlitchesStackText()
{
    if (showGlitchesStack)
    {
        glitchesStackText.str("");
        glitchesStackText << GLITCHSTACK_TITLE << endl;
        glitchesStackSize = 1;

        vector <string> glitchesStack = MSGlitcher::getInstance().getGlitchesStack();
        for (int i=0; i<glitchesStack.size(); ++i) {
            glitchesStackSize++;
            glitchesStackText << glitchesStack[i] << endl;
        }
    }
}
