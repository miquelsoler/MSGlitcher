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
        switch(areaMode)
        {
            case MSGAM_FULL:
            {
                sourcePixels[i] = (unsigned char)(255 - sourcePixels[i]); break;
            }
            case MSGAM_RANDOM:
            {
                break;
            }
            case MSGAM_HORIZONTAL:
            {
                break;
            }
            case MSGAM_VERTICAL:
            {
                break;
            }
            default: break;
        }
    }
}
