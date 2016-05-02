//
// Created by Miquel Àngel Soler on 17/4/16.
//

#ifndef MSGLITCHER_MSGLITCH_H
#define MSGLITCHER_MSGLITCH_H

#include "ofMain.h"

typedef enum
{
    MSGT_NONE               = 0,
    MSGT_INVERT             = 1,
    MSGT_GRAYSCALE          = 2,
    MSGT_RED                = 3,
    MSGT_GREEN              = 4,
    MSGT_BLUE               = 5,
    MSGT_NOISE              = 6,
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

    const MSGlitchType &getType() const { return type; }

protected:

    int videoWidth, videoHeight;

protected:
    MSGlitchType type;

    MSGlitchAreaMode areaMode;
    int areaSize;

    MSGlitchTimerMode timerMode;
    uint64_t timerStartMs;
    uint64_t timerPeriodMs;
    uint64_t timerLength;

    bool hasStarted;
};

#endif //MSGLITCHER_MSGLITCH_H
