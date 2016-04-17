//
// Created by Miquel Àngel Soler on 17/4/16.
//


#include "MSGlitch.h"

MSGlitch::MSGlitch()
{
    areaMode = MSGAM_FULL;
    timerMode = MSGTM_ALWAYS;
}

MSGlitch::~MSGlitch()
{
}

void MSGlitch::setArea(MSGlitchAreaMode _areaMode, int _areaSize)
{
    areaSize = _areaSize;
}

void MSGlitch::setTimer(MSGlitchTimerMode _timerMode)
{
}
