#include "executor/danger_zone_observer.h"
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
    }
    // 兼容未设置区域管理类（ZoneManager）的使用方式
    dangerPointX_ = x;
    dangerPointY_ = y;
    hasDangerPoint_ = true;
    return true;
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
    }
    // 兼容未设置区域管理类（ZoneManager）的使用方式
    hasDangerPoint_ = false;
    return true;
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

    // 兼容未设置区域管理类（ZoneManager）的使用方式
    if (dangerPointX_ == newPosition.x && 
        dangerPointY_ == newPosition.y) {
        alert(IN_DANGEROUS, newPosition.x, newPosition.y);
    }
}