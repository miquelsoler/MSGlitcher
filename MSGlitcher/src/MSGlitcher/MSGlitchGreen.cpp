//
// Created by Miquel Àngel Soler on 17/4/16.
//

#include "MSGlitchGreen.h"

void MSGlitchGreen::update(ofPixels &sourcePixels)
{
    MSGlitch::update(sourcePixels);
    if (!hasStarted) return;

    for (int i=0; i<sourcePixels.size(); ++i)
    {
        if (i % 3 != 1) sourcePixels[i] = 0;
    }
}
