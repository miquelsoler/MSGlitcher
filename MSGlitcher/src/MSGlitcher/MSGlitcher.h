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
#include "MSGlitchNoise.h"


class MSGlitcher
{
public:

    static MSGlitcher &getInstance()
    {
        static MSGlitcher instance;
        return instance;
    }

    void init(int videoWidth, int videoHeight);

    MSGlitch* addGlitch(MSGlitchType glitchType);
    void removeGlitch(MSGlitchType glitchType);
    bool isGlitchAdded(MSGlitchType glitchType);

    void update(ofPixels &sourcePixels);
    void draw(float x, float y, float w, float h);

    int getVideoWidth() const { return videoWidth; }
    int getVideoHeight() const { return videoHeight; }

private:

    int videoWidth, videoHeight;

    vector<MSGlitch *> glitches;

    ofTexture       glitchedTexture;
    ofPixels        glitchedPixels;
};

#endif //MSGLITCHER_MSGLITCHER_H
