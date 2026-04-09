#include "executor/robot_executor.h"

RobotExecutor::RobotExecutor() 
    : initialized_(false)
{}

void RobotExecutor::Initialize(int32_t x, int32_t y, Heading heading)
{
    position_ = Position{x, y, heading};
    initialized_ = true;
}

void RobotExecutor::SetDangerPoint(int32_t x, int32_t y)
{
    dangerPoint_ = Position{x, y, Heading::North};
    hasDangerPoint_ = true;
}

void RobotExecutor::TurnRight()
{
    if (!initialized_) {
        return;
    }
    int32_t newHeading = (static_cast<int32_t>(position_.heading) + 1) % 4;
    position_.heading = static_cast<Heading>(newHeading);
    if (hasDangerPoint_ && 
        dangerPoint_.x == position_.x && 
        dangerPoint_.y == position_.y) {
        alert(IN_DANGEROUS, position_.x, position_.y);
    }
}

void RobotExecutor::TurnLeft()
{
    if (!initialized_) {
        return;
    }
    int32_t newHeading = (static_cast<int32_t>(position_.heading) + 3) % 4;
    position_.heading = static_cast<Heading>(newHeading);
    if (hasDangerPoint_ && 
        dangerPoint_.x == position_.x && 
        dangerPoint_.y == position_.y) {
        alert(IN_DANGEROUS, position_.x, position_.y);
    }
}

void RobotExecutor::Forward()
{
    if (!initialized_) {
        return;
    }
    switch (position_.heading) {
        case Heading::North: 
            position_.y += 1; 
            break;
        case Heading::East:  
            position_.x += 1; 
            break;
        case Heading::South:
            position_.y -= 1; 
            break;
        case Heading::West:  
            position_.x -= 1; 
            break;
        default:
            break;
    }
    if (hasDangerPoint_ && 
        dangerPoint_.x == position_.x && 
        dangerPoint_.y == position_.y) {
        alert(IN_DANGEROUS, position_.x, position_.y);
    }
}

void RobotExecutor::Backward()
{
    if (!initialized_) {
        return;
    }
    switch (position_.heading) {
        case Heading::North:
            position_.y -= 1;
            break;
        case Heading::East:
            position_.x -= 1;
            break;
        case Heading::South:
            position_.y += 1;
            break;
        case Heading::West:
            position_.x += 1;
            break;
        default:
            break;
    }
    if (hasDangerPoint_ && 
        dangerPoint_.x == position_.x && 
        dangerPoint_.y == position_.y) {
        alert(IN_DANGEROUS, position_.x, position_.y);
    }
}

Position RobotExecutor::GetPosition() const
{
    if (!initialized_) {
        return Position{0, 0, Heading::North};
    }
    return position_;
}