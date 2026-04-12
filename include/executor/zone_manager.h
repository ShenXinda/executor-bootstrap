#ifndef ZONE_MANAGER_H
#define ZONE_MANAGER_H

#include "mcl/stdc.h"
#include <cstdint>
#include <array>
#include "robot_common_type.h"

MCL_STDC_BEGIN

enum class ZoneType : int8_t {
    Alert = 0,
    Clean = 1
};

struct ZoneSlot {
    int32_t x {0};
    int32_t y {0};
    ZoneType type {ZoneType::Alert};
    bool active {false};
};

class ZoneManager {
public:
    static constexpr int8_t kMaxSlots = 16;

    ZoneManager();

    bool AddPoint(ZoneType type, int32_t x, int32_t y);
    bool RemovePoint(int32_t x, int32_t y);
    void OnPositionChanged(const Position& newPosition);

    int8_t GetFreeCount() const;
    int8_t GetAlertPointCount() const;
    int8_t GetCleanPointCount() const;

private:
    int8_t FindSlot(int32_t x, int32_t y) const;
    int8_t FindFreeSlot() const;
    void ActivateSlot(int8_t index, ZoneType type, int32_t x, int32_t y);
    void DeactivateSlot(int8_t index);

    std::array<ZoneSlot, kMaxSlots> slots_;
    int8_t alertCount_;
    int8_t cleanCount_;
};

MCL_STDC_END

#endif