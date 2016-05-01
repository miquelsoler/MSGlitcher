//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCHGREEN_H
#define MSGLITCHER_MSGLITCHGREEN_H

#include "MSGlitch.h"

class MSGlitchGreen : public MSGlitch
{
public:

    MSGlitchGreen(int videoWidth, int videoHeight) : MSGlitch(videoWidth, videoHeight) { type = MSGT_GREEN; };
    void update(ofPixels &sourcePixels);

    static string getName() { return "Green"; };
};


#endif //MSGLITCHER_MSGLITCHGREEN_H
