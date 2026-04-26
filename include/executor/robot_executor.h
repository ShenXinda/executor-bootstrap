#ifndef ROBOT_EXECUTOR_H
#define ROBOT_EXECUTOR_H

#include "mcl/stdc.h"
#include "alert/alert.h"
#include "robot_common_type.h"
#include <cstdint>
#include <memory>

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

    bool SetDangerPoint(int32_t x, int32_t y);
    bool ClearDangerPoint();
    bool SetCleanPoint(int32_t x, int32_t y);
    bool ClearCleanPoint();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

MCL_STDC_END

#endif
