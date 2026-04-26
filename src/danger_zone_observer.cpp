#include "executor/private/danger_zone_observer.h"
#include "executor/robot_executor.h"
#include "alert/alert.h"

DangerZoneObserver::DangerZoneObserver(ZoneManager* zoneManager)
    : zoneManager_(zoneManager), hasDangerPoint_(false), dangerPointX_(0), dangerPointY_(0)
{}

bool DangerZoneObserver::SetDangerPoint(int32_t x, int32_t y)
{
    if (hasDangerPoint_) {
        return false;
    }

    if (zoneManager_) {
        if (zoneManager_->AddPoint(ZoneType::Alert, x, y)) {
            dangerPointX_ = x;
            dangerPointY_ = y;
            hasDangerPoint_ = true;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool DangerZoneObserver::ClearDangerPoint()
{
    if (!hasDangerPoint_) {
        return true;
    }

    if (zoneManager_) {
        if (zoneManager_->RemovePoint(dangerPointX_, dangerPointY_)) {
            hasDangerPoint_ = false;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void DangerZoneObserver::OnPositionChanged(const Position& newPosition)
{
    if (!hasDangerPoint_) {
        return;
    }

    if (zoneManager_) {
        zoneManager_->OnPositionChanged(newPosition);
        return;
    }
}