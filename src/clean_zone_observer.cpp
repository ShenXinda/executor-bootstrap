#include "executor/clean_zone_observer.h"
#include "executor/robot_executor.h"
#include "clean/clean.h"

CleanZoneObserver::CleanZoneObserver() 
    : hasCleanPoint_(false), cleanPointX_(0), cleanPointY_(0), hasCleaned_(false)
{}

void CleanZoneObserver::SetCleanPoint(int32_t x, int32_t y)
{
    cleanPointX_ = x;
    cleanPointY_ = y;
    hasCleanPoint_ = true;
}

void CleanZoneObserver::Reset()
{
    hasCleaned_ = false;
}

void CleanZoneObserver::OnPositionChanged(const Position& newPosition)
{
    if (hasCleanPoint_ && 
        !hasCleaned_ &&
        cleanPointX_ == newPosition.x && 
        cleanPointY_ == newPosition.y) {
        clean(newPosition.x, newPosition.y);
        hasCleaned_ = true;
    }
}