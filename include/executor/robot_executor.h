#ifndef ROBOT_EXECUTOR_H
#define ROBOT_EXECUTOR_H

#include "mcl/stdc.h"
#include "alert/alert.h"
#include "robot_common_type.h"
#include "executor/position_observer.h"
#include <cstdint>
#include <memory>
#include <vector>

MCL_STDC_BEGIN

class RobotExecutor
{
public:
    RobotExecutor();
    ~RobotExecutor();

    void Initialize(int32_t x, int32_t y, Heading heading);
    void TurnRight();
    void TurnLeft();
    void TurnRound();
    void Forward();
    void Backward();
    void Forward(int32_t steps);
    void Backward(int32_t steps);
    Position GetPosition() const;

    void RegisterObserver(PositionObserver* observer);
    void UnregisterObserver(PositionObserver* observer);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

MCL_STDC_END

#endif
