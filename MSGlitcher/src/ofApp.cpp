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

    int x = 10;
    int y = 10, yIncr = 10;
    ofDrawBitmapString("KEYS", x, y += yIncr);
    ofDrawBitmapString("1: Invert", x, y += yIncr);
    ofDrawBitmapString("2: Grayscale", x, y += yIncr);
    ofDrawBitmapString("3: Red", x, y += yIncr);
    ofDrawBitmapString("4: Green", x, y += yIncr);
    ofDrawBitmapString("5: Blue", x, y += yIncr);
    ofDrawBitmapString("6: Noise", x, y += yIncr);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    MSGlitcher &glitcher = MSGlitcher::getInstance();
    MSGlitchType glitchType;

    switch(key)
    {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
        case '1': // Invert
        {
            glitchType = MSGT_INVERT;
            if (!glitcher.isGlitchAdded(glitchType))
            {
                MSGlitchInvert *glitch = dynamic_cast<MSGlitchInvert *>(glitcher.addGlitch(glitchType));
                glitch->setTimer(MSGTM_TIMED, 0, 0);
            } else {
                glitcher.removeGlitch(glitchType);
            }
            break;
        }
        case '2': // Grayscale
        {
            glitchType = MSGT_GRAYSCALE;
            if (!glitcher.isGlitchAdded(glitchType))
            {
                MSGlitchGrayscale *glitch = dynamic_cast<MSGlitchGrayscale *>(glitcher.addGlitch(glitchType));
                glitch->setTimer(MSGTM_TIMED, 0, 0);
            } else {
                glitcher.removeGlitch(glitchType);
            }
            break;
        }
        case '3': // Red
        {
            glitchType = MSGT_RED;
            if (!glitcher.isGlitchAdded(glitchType))
            {
                MSGlitchRed *glitch = dynamic_cast<MSGlitchRed *>(glitcher.addGlitch(glitchType));
                glitch->setTimer(MSGTM_TIMED, 0, 0);
            } else {
                glitcher.removeGlitch(glitchType);
            }
            break;
        }
        case '4': // Green
        {
            glitchType = MSGT_GREEN;
            if (!glitcher.isGlitchAdded(glitchType))
            {
                MSGlitchGreen *glitch = dynamic_cast<MSGlitchGreen *>(glitcher.addGlitch(glitchType));
                glitch->setTimer(MSGTM_TIMED, 0, 0);
            } else {
                glitcher.removeGlitch(glitchType);
            }
            break;
        }
        case '5': // Blue
        {
            glitchType = MSGT_BLUE;
            if (!glitcher.isGlitchAdded(glitchType))
            {
                MSGlitchBlue *glitch = dynamic_cast<MSGlitchBlue *>(glitcher.addGlitch(glitchType));
                glitch->setTimer(MSGTM_TIMED, 0, 0);
            } else {
                glitcher.removeGlitch(glitchType);
            }
            break;
        }
        case '6': // Noise
        {
            glitchType = MSGT_NOISE;
            if (!glitcher.isGlitchAdded(glitchType))
            {
                MSGlitchNoise *glitch = dynamic_cast<MSGlitchNoise *>(glitcher.addGlitch(glitchType));
                glitch->setTimer(MSGTM_TIMED, 0, 0);
            } else {
                glitcher.removeGlitch(glitchType);
            }
            break;
        }
        default: break;
    }
}
