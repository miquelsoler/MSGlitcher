//
// Created by Miquel Àngel Soler on 17/4/16.
//


#include "MSGlitcher.h"

void MSGlitcher::init(int _videoWidth, int _videoHeight)
{
    videoWidth = _videoWidth;
    videoHeight = _videoHeight;

    glitchedPixels.allocate(videoWidth, videoHeight, OF_PIXELS_RGB);
    glitchedTexture.allocate(glitchedPixels);
}

MSGlitch* MSGlitcher::addGlitch(MSGlitchType glitchType)
{
    if (isGlitchAdded(glitchType)) return;

    MSGlitch *glitch = NULL;
    switch(glitchType)
    {
        case MSGT_INVERT:       glitch = new MSGlitchInvert(videoWidth, videoHeight); break;
        case MSGT_GRAYSCALE:    glitch = new MSGlitchGrayscale(videoWidth, videoHeight); break;
        case MSGT_RED: { // R, G and B glitches are mutually exclusive
            glitch = new MSGlitchRed(videoWidth, videoHeight);
            removeGlitch(MSGT_GREEN);
            removeGlitch(MSGT_BLUE);
            break;
        }
        case MSGT_GREEN: { // R, G and B glitches are mutually exclusive
            glitch = new MSGlitchGreen(videoWidth, videoHeight);
            removeGlitch(MSGT_RED);
            removeGlitch(MSGT_BLUE);
            break;
        }
        case MSGT_BLUE: { // R, G and B glitches are mutually exclusive
            glitch = new MSGlitchBlue(videoWidth, videoHeight);
            removeGlitch(MSGT_RED);
            removeGlitch(MSGT_GREEN);
            break;
        }
        case MSGT_NOISE:        glitch = new MSGlitchNoise(videoWidth, videoHeight); break;
        default: break;
    }

    if (glitch != NULL) glitches.push_back(glitch);
    return glitch;
}

void MSGlitcher::removeGlitch(MSGlitchType glitchType)
{
    if (!isGlitchAdded(glitchType)) return;

    int glitchIndex = 0;
    bool found = false;
    for (int i=0; i<glitches.size() && !found; ++i) {
        if (glitches[i]->getType() == glitchType) {
            glitchIndex = i;
            found = true;
        }
    }

    if (found) {
        delete glitches[glitchIndex];
        glitches.erase(glitches.begin() + glitchIndex);
    }
}

bool MSGlitcher::isGlitchAdded(MSGlitchType glitchType)
{
    for (int i=0; i<glitches.size(); ++i) {
        if (glitches[i]->getType() == glitchType)
            return true;
    }

    return false;
}

void MSGlitcher::update(ofPixels &sourcePixels)
{
    for (int i=0; i<sourcePixels.size(); ++i) {
        glitchedPixels[i] = sourcePixels[i];
    }

    for (int i=0; i<glitches.size(); ++i) {
        glitches[i]->update(glitchedPixels);
    }

    glitchedTexture.loadData(glitchedPixels);
}

void MSGlitcher::draw(float x, float y, float w, float h)
{
    glitchedTexture.draw(x, y, w, h);
}

vector<string> MSGlitcher::getGlitchesStack()
{
    vector<string> result;
    if (glitches.size() == 0) return result;

    for (int i=int(glitches.size()-1); i>=0; i--) {
        MSGlitchType glitchType = glitches[i]->getType();
        switch(glitchType) {
            case MSGT_INVERT:       result.push_back(MSGlitchInvert::getName()); break;
            case MSGT_GRAYSCALE:    result.push_back(MSGlitchGrayscale::getName()); break;
            case MSGT_RED:          result.push_back(MSGlitchRed::getName()); break;
            case MSGT_GREEN:        result.push_back(MSGlitchGreen::getName()); break;
            case MSGT_BLUE:         result.push_back(MSGlitchBlue::getName()); break;
            case MSGT_NOISE:        result.push_back(MSGlitchNoise::getName()); break;
            default: break;
        }
    }

    return result;
}
