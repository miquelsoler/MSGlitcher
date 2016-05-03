//
// Created by Miquel Àngel Soler on 17/4/16.
//


#include "MSGlitchInvert.h"

void MSGlitchInvert::update(ofPixels &sourcePixels)
{
    MSGlitch::update(sourcePixels);
    if (!hasStarted) return;

    for (int i=0; i<sourcePixels.size(); ++i)
    {
        sourcePixels[i] = (unsigned char)(255 - sourcePixels[i]);
    }
}
