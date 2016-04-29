//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCHGRAYSCALE_H
#define MSGLITCHER_MSGLITCHGRAYSCALE_H

#include "MSGlitch.h"

class MSGlitchGrayscale : public MSGlitch
{
public:

    MSGlitchGrayscale(int videoWidth, int videoHeight) : MSGlitch(videoWidth, videoHeight) { type = MSGT_GRAYSCALE; };
    void update(ofPixels &sourcePixels);
};

#endif //MSGLITCHER_MSGLITCHGRAYSCALE_H
