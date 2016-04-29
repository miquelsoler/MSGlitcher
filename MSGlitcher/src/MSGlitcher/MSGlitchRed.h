//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCHRED_H
#define MSGLITCHER_MSGLITCHRED_H

#include "MSGlitch.h"

class MSGlitchRed : public MSGlitch
{
public:
    
    MSGlitchRed(int videoWidth, int videoHeight) : MSGlitch(videoWidth, videoHeight) { type = MSGT_RED; };
    void update(ofPixels &sourcePixels);
};

#endif //MSGLITCHER_MSGLITCHRED_H
