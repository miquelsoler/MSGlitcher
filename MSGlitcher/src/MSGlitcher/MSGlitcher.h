//
//  MSGlitcher.hpp
//  Test1
//
//  Created by Miquel Àngel Soler on 17/4/16.
//
//

#ifndef MSGlitcher_h
#define MSGlitcher_h

#include <stdio.h>
#include "ofMain.h"
#include "MSGlitchInvert.h"
#include "MSGlitchGrayscale.h"

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

    void update(ofPixels &sourcePixels);
    void draw(float x, float y, float w, float h);

private:

    int videoWidth, videoHeight;

    vector<MSGlitch *> glitches;

    ofTexture       glitchedTexture;
    ofPixels        glitchedPixels;
};

#endif /* MSGlitcher_h */
