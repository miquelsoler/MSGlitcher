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
    switch(glitchType)
    {
        case MSGT_INVERT: {
            MSGlitchInvert *glitch = new MSGlitchInvert();
            glitches.push_back(glitch);
            return glitch;
        }
        case MSGT_GRAYSCALE: {
            MSGlitchGrayscale *glitch = new MSGlitchGrayscale();
            glitches.push_back(glitch);
            return glitch;
        }
        default:
        {
            return NULL;
        }
    }
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
