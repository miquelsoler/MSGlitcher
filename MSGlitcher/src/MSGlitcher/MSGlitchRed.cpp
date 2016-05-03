//
// Created by Miquel Àngel Soler on 17/4/16.
//

#include "MSGlitchRed.h"

void MSGlitchRed::update(ofPixels &sourcePixels)
{
    MSGlitch::update(sourcePixels);
    if (!hasStarted) return;

    for (int i=0; i<sourcePixels.size(); ++i)
    {
        if (i % 3 != 0) sourcePixels[i] = 0;
    }
}
