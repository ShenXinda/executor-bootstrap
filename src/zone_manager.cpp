#include "executor/zone_manager.h"
#include "alert/alert.h"
#include "clean/clean.h"

ZoneManager::ZoneManager()
    : alertCount_(0), cleanCount_(0)
{
    for (auto& slot : slots_) {
        slot.active = false;
    }
}

bool ZoneManager::AddPoint(ZoneType type, int32_t x, int32_t y)
{
    int8_t existing = FindSlot(x, y);
    if (existing >= 0) {
        return false;
    }

    int8_t freeSlot = FindFreeSlot();
    if (freeSlot < 0) {
        return false;
    }

    ActivateSlot(freeSlot, type, x, y);
    return true;
}

bool ZoneManager::RemovePoint(int32_t x, int32_t y)
{
    int8_t index = FindSlot(x, y);
    if (index < 0) {
        return false;
    }
    DeactivateSlot(index);
    return true;
}

void ZoneManager::OnPositionChanged(const Position& newPosition)
{
    for (int8_t i = 0; i < kMaxSlots; ++i) {
        if (!slots_[i].active) {
            continue;
        }
        if (slots_[i].x == newPosition.x && slots_[i].y == newPosition.y) {
            if (slots_[i].type == ZoneType::Alert) {
                alert(IN_DANGEROUS, newPosition.x, newPosition.y);
            } else if (slots_[i].type == ZoneType::Clean) {
                clean(newPosition.x, newPosition.y);
                DeactivateSlot(i); // 清扫后自动回收⼀个坐标点的配置资源
            }
        }
    }
}

int8_t ZoneManager::GetFreeCount() const
{
    return kMaxSlots - alertCount_ - cleanCount_;
}

int8_t ZoneManager::GetAlertPointCount() const
{
    return alertCount_;
}

int8_t ZoneManager::GetCleanPointCount() const
{
    return cleanCount_;
}

int8_t ZoneManager::FindSlot(int32_t x, int32_t y) const
{
    for (int8_t i = 0; i < kMaxSlots; ++i) {
        if (slots_[i].active && slots_[i].x == x && slots_[i].y == y) {
            return i;
        }
    }
    return -1;
}

int8_t ZoneManager::FindFreeSlot() const
{
    for (int8_t i = 0; i < kMaxSlots; ++i) {
        if (!slots_[i].active) {
            return i;
        }
    }
    return -1;
}

void ZoneManager::ActivateSlot(int8_t index, ZoneType type, int32_t x, int32_t y)
{
    slots_[index].x = x;
    slots_[index].y = y;
    slots_[index].type = type;
    slots_[index].active = true;

    if (type == ZoneType::Alert) {
        ++alertCount_;
    } else {
        ++cleanCount_;
    }
}

void ZoneManager::DeactivateSlot(int8_t index)
{
    if (!slots_[index].active) {
        return;
    }

    if (slots_[index].type == ZoneType::Alert) {
        --alertCount_;
    } else {
        --cleanCount_;
    }
    slots_[index].active = false;
}