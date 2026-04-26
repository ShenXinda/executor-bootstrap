#include "executor/private/clean_zone_observer.h"
#include "executor/robot_executor.h"
#include "clean/clean.h"

CleanZoneObserver::CleanZoneObserver(ZoneManager* zoneManager)
    : zoneManager_(zoneManager), hasCleanPoint_(false), cleanPointX_(0), cleanPointY_(0), hasCleaned_(false)
{}

bool CleanZoneObserver::SetCleanPoint(int32_t x, int32_t y)
{
    if (hasCleanPoint_) {
        return false;
    }

    if (zoneManager_) {
        if (zoneManager_->AddPoint(ZoneType::Clean, x, y)) {
            cleanPointX_ = x;
            cleanPointY_ = y;
            hasCleanPoint_ = true;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool CleanZoneObserver::ClearCleanPoint()
{
    if (!hasCleanPoint_) {
        return true;
    }

    if (zoneManager_) {
        if (zoneManager_->RemovePoint(cleanPointX_, cleanPointY_)) {
            hasCleanPoint_ = false;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void CleanZoneObserver::Reset()
{
    hasCleaned_ = false;
}

void CleanZoneObserver::OnPositionChanged(const Position& newPosition)
{
    if (!hasCleanPoint_ || hasCleaned_) {
        return;
    }

    if (zoneManager_) {
        zoneManager_->OnPositionChanged(newPosition);
        hasCleaned_ = true;
        return;
    }
}