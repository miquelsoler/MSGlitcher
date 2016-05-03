//
// Created by Miquel Àngel Soler on 28/4/16.
//

#include "MSGlitchNoise.h"

static const float NOISE_AMOUNT = 0.5f;
static const float NOISE_STRENGTH = 0.1f;

void MSGlitchNoise::update(ofPixels &sourcePixels)
{
    MSGlitch::update(sourcePixels);
    if (!hasStarted) return;

    for (int i=0; i<sourcePixels.size(); i+=3)
    {
        if (ofInRange(ofRandom(0, 1), 0.0f, NOISE_AMOUNT))
        {
            float noiseStrength = 1.0f - NOISE_STRENGTH;
            sourcePixels[i + 0] *= noiseStrength;
            sourcePixels[i + 1] *= noiseStrength;
            sourcePixels[i + 2] *= noiseStrength;
        }
    }
}
