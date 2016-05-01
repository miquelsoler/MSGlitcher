#include "ofApp.h"

#include "MSGlitcher.h"

static const int GUI_GLITCHES_OFFSET = 10;

//--------------------------------------------------------------
void ofApp::setup()
{
    // Get video devices

    vector<ofVideoDevice> videoDevices = videoGrabber.listDevices();
    vector<int> availableVideoDevices;
    cout << endl << "VIDEO DEVICES" << endl;
    for (int i=0; i<videoDevices.size(); ++i)
    {
        ofVideoDevice &device = videoDevices[i];
        cout << "-------------------" << endl;
        cout << "Name:      \"" << device.deviceName << "\"" << endl;
        cout << "Id:        \"" << device.id << "\""  << endl;
        cout << "Hardware:  \"" << device.hardwareName << "\""  << endl;
        cout << "Available: \"" << (device.bAvailable ? "true" : "false") << "\""  << endl;

        if (!device.bAvailable) continue;

        availableVideoDevices.push_back(device.id);
    }

    if (availableVideoDevices.size() < 1)
    {
        cout << "No available video devices. Exiting..." << endl;
        std::exit(EXIT_FAILURE);
    }

    // Create video grabber

    int videoWidth = 1024;
    int videoHeight = 576;

    videoGrabber.setDeviceID(availableVideoDevices[0]);
    videoGrabber.setDesiredFrameRate(30);
    videoGrabber.setup(videoWidth, videoHeight);

    // Setup glitches GUI

    guiGlitches = new ofxDatGui(GUI_GLITCHES_OFFSET, GUI_GLITCHES_OFFSET + ofGetHeight()/2);
    guiGlitches->setWidth(120);

    guiGlitches->addHeader("GLITCHES");
    guiGlitches->addBreak();

    guiGlitches->addFRM();
    guiGlitches->addBreak();

    guiGlitches->addToggle(MSGlitchInvert::getName(), false);
    guiGlitches->addToggle(MSGlitchGrayscale::getName(), false);
    guiGlitches->addToggle(MSGlitchRed::getName(), false);
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
    videoGrabber.update();

    if (videoGrabber.isFrameNew()) {
        MSGlitcher::getInstance().update(videoGrabber.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    videoGrabber.draw(0, 0, ofGetWidth()/2, ofGetHeight()/2);
    MSGlitcher::getInstance().draw(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    MSGlitcher &glitcher = MSGlitcher::getInstance();

    switch(key)
    {
        case 'f':
        case 'F':
        {
            ofToggleFullscreen();
            guiGlitches->setPosition(GUI_GLITCHES_OFFSET, GUI_GLITCHES_OFFSET + ofGetHeight()/2);
            break;
        }
        case 'g':
        {
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
