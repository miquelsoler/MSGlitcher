//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCHBLUE_H
#define MSGLITCHER_MSGLITCHBLUE_H

#include "MSGlitch.h"

class MSGlitchBlue : public MSGlitch
{
public:

    MSGlitchBlue(int videoWidth, int videoHeight) : MSGlitch(videoWidth, videoHeight) { type = MSGT_BLUE; };
    void update(ofPixels &sourcePixels);
};


#endif //MSGLITCHER_MSGLITCHBLUE_H
