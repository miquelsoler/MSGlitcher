//
// Created by Miquel Àngel Soler on 17/4/16.
//

#include "MSGlitchGreen.h"

void MSGlitchGreen::update(ofPixels &sourcePixels)
{
    for (int i=0; i<sourcePixels.size(); ++i)
    {
        switch(areaMode)
        {
            case MSGAM_FULL:
            {
                if (i % 3 != 1) sourcePixels[i] = 0; break;
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
