//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCH_H
#define MSGLITCHER_MSGLITCH_H

#include "ofMain.h"

typedef enum
{
    MSGT_INVERT             = 0,
    MSGT_GRAYSCALE          = 1,
    MSGT_RED                = 2,
    MSGT_GREEN              = 3,
    MSGT_BLUE               = 4,
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
    MSGTM_ALWAYS    = 0,
    MSGTM_RANDOM    = 1,
    MSGTM_TIMED     = 2
} MSGlitchTimerMode;


class MSGlitch
{
public:

    MSGlitch(int videoWidth, int videoHeight);
    ~MSGlitch();

    void setArea(MSGlitchAreaMode areaMode, int areaSizeInPixels = 0);
    void setTimer(MSGlitchTimerMode timerMode, uint64_t timerStartMs = 0, uint64_t timerPeriodMs = 0, uint64_t timerLength = 0);

    virtual void update(ofPixels &sourcePixels);

protected:

    int videoWidth, videoHeight;

    MSGlitchAreaMode areaMode;
    int areaSize;

    MSGlitchTimerMode timerMode;
    uint64_t timerStartMs;
    uint64_t timerPeriodMs;
    uint64_t timerLength;

    bool hasStarted;
};

#endif //MSGLITCHER_MSGLITCH_H
