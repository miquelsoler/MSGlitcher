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

    hasStarted = false;
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

void MSGlitch::setTimer(MSGlitchTimerMode _timerMode, uint64_t _timerStartMs, uint64_t _timerPeriodMs, uint64_t _timerLength)
{
    timerMode = _timerMode;
    timerStartMs = ofGetElapsedTimeMillis() + _timerStartMs;
    timerPeriodMs = _timerPeriodMs;
    timerLength = (_timerPeriodMs < _timerLength) ? _timerLength : _timerPeriodMs;
}

void MSGlitch::update(ofPixels &sourcePixels)
{
    hasStarted = (timerMode == MSGTM_ALWAYS) || (ofGetElapsedTimeMillis() > timerStartMs);
}
