//
// Created by Miquel Àngel Soler on 17/4/16.
//

#include "MSGlitchGrayscale.h"

void MSGlitchGrayscale::update(ofPixels &sourcePixels)
{
//    The average method simply averages the values: (R + G + B) / 3.


    for (int i=0; i<sourcePixels.size(); i+=3) {
        int r = sourcePixels[i+0];
        int g = sourcePixels[i+1];
        int b = sourcePixels[i+2];
        int average = (r + g + b) / 3;
        sourcePixels[i + 0] = (unsigned char)average;
        sourcePixels[i + 1] = (unsigned char)average;
        sourcePixels[i + 2] = (unsigned char)average;
    }
}
