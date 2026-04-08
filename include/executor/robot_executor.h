#ifndef ROBOT_EXECUTOR_H
#define ROBOT_EXECUTOR_H

#include "mcl/stdc.h"
#include <cstdint>

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
    void TurnRight();
    void TurnLeft();
    void Forward();
    void Backward();
    Position GetPosition() const;

private:
    Position position_;
    bool initialized_ {false};
};

#endif
