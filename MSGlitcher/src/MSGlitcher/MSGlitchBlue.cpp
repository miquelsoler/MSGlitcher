//
// Created by Miquel Àngel Soler on 17/4/16.
//

#include "MSGlitchBlue.h"

void MSGlitchBlue::update(ofPixels &sourcePixels)
{
    MSGlitch::update(sourcePixels);
    if (!hasStarted) return;

    for (int i=0; i<sourcePixels.size(); ++i)
    {
        switch(areaMode)
        {
            case MSGAM_FULL:
            {
                if (i % 3 != 2) sourcePixels[i] = 0; break;
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
