#include "executor/danger_zone_observer.h"
#include "executor/robot_executor.h"
#include "alert/alert.h"

DangerZoneObserver::DangerZoneObserver() 
    : hasDangerPoint_(false), dangerPointX_(0), dangerPointY_(0)
{}

void DangerZoneObserver::SetDangerPoint(int32_t x, int32_t y)
{
    dangerPointX_ = x;
    dangerPointY_ = y;
    hasDangerPoint_ = true;
}

void DangerZoneObserver::ClearDangerPoint()
{
    hasDangerPoint_ = false;
}

void DangerZoneObserver::OnPositionChanged(const Position& newPosition)
{
    if (hasDangerPoint_ && 
        dangerPointX_ == newPosition.x && 
        dangerPointY_ == newPosition.y) {
        alert(IN_DANGEROUS, newPosition.x, newPosition.y);
    }
}