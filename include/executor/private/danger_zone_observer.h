#ifndef DANGER_ZONE_OBSERVER_H
#define DANGER_ZONE_OBSERVER_H

#include "mcl/stdc.h"
#include "executor/private/position_observer.h"
#include "executor/private/zone_manager.h"
#include <cstdint>

MCL_STDC_BEGIN

class DangerZoneObserver final : public PositionObserver {
public:
    explicit DangerZoneObserver(ZoneManager* zoneManager = nullptr);

    bool SetDangerPoint(int32_t x, int32_t y);
    bool ClearDangerPoint();

    void OnPositionChanged(const Position& newPosition) override;

private:
    ZoneManager* zoneManager_;
    bool hasDangerPoint_;
    int32_t dangerPointX_;
    int32_t dangerPointY_;
};

MCL_STDC_END

#endif