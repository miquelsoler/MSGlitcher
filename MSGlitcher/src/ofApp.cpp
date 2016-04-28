#include "ofApp.h"

#include "MSGlitcher.h"

//--------------------------------------------------------------
void ofApp::setup()
{
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

    int videoWidth = 1024;
    int videoHeight = 576;

    videoGrabber.setDeviceID(availableVideoDevices[0]);
    videoGrabber.setDesiredFrameRate(30);
    videoGrabber.setup(videoWidth, videoHeight);
    cout << "w=" << videoGrabber.getWidth() << "- h=" << videoGrabber.getHeight() << endl;

    MSGlitcher::getInstance().init(videoWidth, videoHeight);

//    // Add glich: grayscale
//    MSGlitchGrayscale *glitchGrayscale = dynamic_cast<MSGlitchGrayscale *>(MSGlitcher::getInstance().addGlitch(videoWidth, videoHeight, MSGT_GRAYSCALE));
//    glitchGrayscale->setTimer(MSGTM_TIMED, 0, 0);

    // Add glich: red
    MSGlitchRed *glitchRed = dynamic_cast<MSGlitchRed *>(MSGlitcher::getInstance().addGlitch(videoWidth, videoHeight, MSGT_RED));
    glitchRed->setTimer(MSGTM_TIMED, 0, 0);

    // Add glich: noise
    MSGlitchNoise *glitchNoise = dynamic_cast<MSGlitchNoise *>(MSGlitcher::getInstance().addGlitch(videoWidth, videoHeight, MSGT_NOISE));
    glitchNoise->setTimer(MSGTM_TIMED, 0, 0);

//    // Add glich: invert
//    MSGlitchInvert *glitchInvert = dynamic_cast<MSGlitchInvert *>(MSGlitcher::getInstance().addGlitch(videoWidth, videoHeight, MSGT_INVERT));
//    glitchInvert->setTimer(MSGTM_TIMED, 0, 0);

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
    switch(key)
    {
        case 'f':
        case 'F':
        {
            ofToggleFullscreen();
            break;
        }
    }
}
