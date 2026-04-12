#ifndef POSITION_OBSERVER_H
#define POSITION_OBSERVER_H

#include "mcl/stdc.h"
#include "robot_common_type.h"

MCL_STDC_BEGIN

class PositionObserver {
public:
    virtual ~PositionObserver() = default;
    virtual void OnPositionChanged(const Position& newPosition) = 0;
};

MCL_STDC_END

#endif