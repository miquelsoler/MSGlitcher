//
//  MSGlitch.hpp
//  Test1
//
//  Created by Miquel Àngel Soler on 17/4/16.
//
//

#ifndef MSGlitch_h
#define MSGlitch_h

#include "ofMain.h"

typedef enum
{
    MSGT_INVERT             = 0,
    MSGT_GRAYSCALE          = 1
} MSGlitchType;

typedef enum
{
    MSGAM_FULL          = 0,
    MSGAM_RANDOM        = 1,
    MSGAM_HORIZONTAL    = 2,
    MSGAM_VERTICAL      = 3
} MSGlitchAreaMode;

typedef enum
{
    MSGTM_ALWAYS = 0,
    MSGTM_RANDOM = 1
} MSGlitchTimerMode;


class MSGlitch
{
public:

    MSGlitch();
    ~MSGlitch();

    void setArea(MSGlitchAreaMode areaMode, int areaSize);
    void setTimer(MSGlitchTimerMode timerMode);

    virtual void update(ofPixels &sourcePixels) = 0;

protected:

    MSGlitchAreaMode areaMode;
    int areaSize;

    MSGlitchTimerMode timerMode;
};

#endif /* MSGlitch_h */
