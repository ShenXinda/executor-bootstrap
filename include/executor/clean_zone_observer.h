#ifndef CLEAN_ZONE_OBSERVER_H
#define CLEAN_ZONE_OBSERVER_H

#include "mcl/stdc.h"
#include "executor/position_observer.h"
#include <cstdint>

MCL_STDC_BEGIN

class CleanZoneObserver final : public PositionObserver {
public:
    explicit CleanZoneObserver();

    void SetCleanPoint(int32_t x, int32_t y);
    void Reset();

    void OnPositionChanged(const Position& newPosition) override;

private:
    bool hasCleanPoint_;
    int32_t cleanPointX_;
    int32_t cleanPointY_;
    bool hasCleaned_;
};

MCL_STDC_END

#endif