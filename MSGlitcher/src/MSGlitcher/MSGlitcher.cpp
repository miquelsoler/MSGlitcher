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

MSGlitch* MSGlitcher::addGlitch(int videoWidth, int videoHeight, MSGlitchType glitchType)
{
    MSGlitch *glitch = NULL;
    switch(glitchType)
    {
        case MSGT_INVERT:       glitch = new MSGlitchInvert(videoWidth, videoHeight); break;
        case MSGT_GRAYSCALE:    glitch = new MSGlitchGrayscale(videoWidth, videoHeight); break;
        case MSGT_RED:          glitch = new MSGlitchRed(videoWidth, videoHeight); break;
        case MSGT_GREEN:        glitch = new MSGlitchGreen(videoWidth, videoHeight); break;
        case MSGT_BLUE:         glitch = new MSGlitchBlue(videoWidth, videoHeight); break;
        default: break;
    }

    if (glitch != NULL) glitches.push_back(glitch);
    return glitch;
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
