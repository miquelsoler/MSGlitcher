//
// Created by Miquel Àngel Soler on 17/4/16.
//

#include "MSGlitchGrayscale.h"

void MSGlitchGrayscale::update(ofPixels &sourcePixels)
{
    MSGlitch::update(sourcePixels);
    if (!hasStarted) return;

    for (int i=0; i<sourcePixels.size(); ++i)
    {
        switch(areaMode)
        {
            case MSGAM_FULL:
            {
                int r = sourcePixels[i+0];
                int g = sourcePixels[i+1];
                int b = sourcePixels[i+2];
                int average = (r + g + b) / 3;
                sourcePixels[i + 0] = (unsigned char)average;
                sourcePixels[i + 1] = (unsigned char)average;
                sourcePixels[i + 2] = (unsigned char)average;
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
