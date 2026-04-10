#ifndef POSITION_OBSERVER_H
#define POSITION_OBSERVER_H

#include "mcl/stdc.h"
#include <cstdint>

MCL_STDC_BEGIN

enum class Heading : int32_t;
struct Position;

class PositionObserver {
public:
    virtual ~PositionObserver() = default;
    virtual void OnPositionChanged(const Position& newPosition) = 0;
};

MCL_STDC_END

#endif