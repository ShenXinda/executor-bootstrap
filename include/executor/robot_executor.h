#ifndef ROBOT_EXECUTOR_H
#define ROBOT_EXECUTOR_H

#include "mcl/stdc.h"
#include "alert/alert.h"
#include "executor/position_observer.h"
#include <cstdint>
#include <vector>

MCL_STDC_BEGIN

enum class Heading : int32_t {
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

struct Position {
    int32_t x {0};
    int32_t y {0};
    Heading heading {Heading::North};
};

class RobotExecutor {
public:
    RobotExecutor();

    void Initialize(int32_t x, int32_t y, Heading heading);
    void SetDangerPoint(int32_t x, int32_t y);
    void TurnRight();
    void TurnLeft();
    void Forward();
    void Backward();
    Position GetPosition() const;

    void RegisterObserver(PositionObserver* observer);
    void UnregisterObserver(PositionObserver* observer);

private:
    void NotifyPositionChanged();

    Position position_;
    bool initialized_ {false};
    bool hasDangerPoint_ {false};
    Position dangerPoint_;
    std::vector<PositionObserver*> observers_;
};

MCL_STDC_END

#endif
