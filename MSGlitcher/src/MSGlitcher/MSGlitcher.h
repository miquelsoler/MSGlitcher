//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCHER_H
#define MSGLITCHER_MSGLITCHER_H

#include "ofMain.h"
#include "MSGlitchInvert.h"
#include "MSGlitchGrayscale.h"
#include "MSGlitchRed.h"
#include "MSGlitchGreen.h"
#include "MSGlitchBlue.h"


class MSGlitcher
{
public:

    static MSGlitcher &getInstance()
    {
        static MSGlitcher instance;
        return instance;
    }

    void init(int videoWidth, int videoHeight);

    MSGlitch* addGlitch(int videoWidth, int videoHeight, MSGlitchType glitchType);

    void update(ofPixels &sourcePixels);
    void draw(float x, float y, float w, float h);

private:

    int videoWidth, videoHeight;

    vector<MSGlitch *> glitches;

    ofTexture       glitchedTexture;
    ofPixels        glitchedPixels;
};

#endif //MSGLITCHER_MSGLITCHER_H
