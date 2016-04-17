#include "ofApp.h"

#include "MSGlitcher.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    vector<ofVideoDevice> videoDevices = videoGrabber.listDevices();
    vector<int> availableVideoDevices;
    for (int i=0; i<videoDevices.size(); ++i)
    {
        ofVideoDevice &device = videoDevices[i];
        cout << "-------------------" << endl;
        cout << "Name:      \"" << device.deviceName << "\"" << endl;
        cout << "Id:        \"" << device.id << "\""  << endl;
        cout << "Hardware:  \"" << device.hardwareName << "\""  << endl;
        cout << "Available: \"" << device.bAvailable << "\""  << endl;

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
    videoGrabber.initGrabber(videoWidth, videoHeight);

    MSGlitcher::getInstance().init(videoWidth, videoHeight);
    MSGlitcher::getInstance().addGlitch(MSGT_GRAYSCALE);

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
