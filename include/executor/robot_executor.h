#ifndef ROBOT_EXECUTOR_H
#define ROBOT_EXECUTOR_H

#include "mcl/stdc.h"
#include <optional>

enum class Heading : int {
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

struct Position {
    int x;
    int y;
    Heading heading;
};

class RobotExecutor {
public:
    RobotExecutor();

    void Initialize(int x, int y, Heading heading);
    void TurnRight();
    void TurnLeft();
    Position GetPosition() const;

private:
    std::optional<Position> position_;
};

#endif
