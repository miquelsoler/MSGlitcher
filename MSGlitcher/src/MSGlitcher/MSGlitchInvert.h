//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCHINVERT_H
#define MSGLITCHER_MSGLITCHINVERT_H

#include "MSGlitch.h"

class MSGlitchInvert : public MSGlitch
{
public:

    MSGlitchInvert(int videoWidth, int videoHeight) : MSGlitch(videoWidth, videoHeight) { type = MSGT_INVERT; };
    void update(ofPixels &sourcePixels);
};

#endif //MSGLITCHER_MSGLITCHINVERT_H
