//
// Created by Miquel Àngel Soler on 28/4/16.
//

#ifndef MSGLITCHER_MSGLITCHNOISE_H
#define MSGLITCHER_MSGLITCHNOISE_H

#include "MSGlitch.h"

class MSGlitchNoise : public MSGlitch
{
public:

    MSGlitchNoise(int videoWidth, int videoHeight) : MSGlitch(videoWidth, videoHeight) { type = MSGT_NOISE; };
    void update(ofPixels &sourcePixels);

    static string getName() { return "Noise"; };
};


#endif //MSGLITCHER_MSGLITCHNOISE_H
