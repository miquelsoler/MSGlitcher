//
// Created by Miquel Àngel Soler on 17/4/16.
//


#include "MSGlitch.h"

MSGlitch::MSGlitch(int _videoWidth, int _videoHeight)
{
    videoWidth = _videoWidth;
    videoHeight = _videoHeight;

    areaMode = MSGAM_FULL;
    timerMode = MSGTM_ALWAYS;
}

MSGlitch::~MSGlitch()
{
}

void MSGlitch::setArea(MSGlitchAreaMode _areaMode, int _areaSize)
{
    areaMode = _areaMode;
    areaSize = _areaSize;

    switch (areaMode)
    {
        default: break;
    }
}

void MSGlitch::setTimer(MSGlitchTimerMode _timerMode)
{
}
