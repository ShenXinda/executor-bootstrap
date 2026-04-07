#include "executor/robot_executor.h"
#include <cassert>

RobotExecutor::RobotExecutor() = default;

void RobotExecutor::Initialize(int x, int y, Heading heading) {
    position_ = Position{x, y, heading};
}

void RobotExecutor::TurnRight() {
    if (!position_.has_value()) {
        return;
    }
    int newHeading = (static_cast<int>(position_->heading) + 1) % 4;
    position_->heading = static_cast<Heading>(newHeading);
}

void RobotExecutor::TurnLeft() {
    if (!position_.has_value()) {
        return;
    }
    int newHeading = (static_cast<int>(position_->heading) + 3) % 4;
    position_->heading = static_cast<Heading>(newHeading);
}

Position RobotExecutor::GetPosition() const {
    if (!position_.has_value()) {
        return Position{0, 0, Heading::North};
    }
    return position_.value();
}
