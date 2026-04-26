#include "executor/robot_executor.h"
#include "executor/robot_common_type.h"
#include "executor/private/danger_zone_observer.h"
#include "executor/private/clean_zone_observer.h"
#include "executor/private/zone_manager.h"

class RobotExecutor::Impl
{
private:
    Position position_;
    bool initialized_ {false};
    ZoneManager zoneManager_;
    DangerZoneObserver dangerObserver_;
    CleanZoneObserver cleanObserver_;

public:
    Impl()
        : initialized_(false), 
          dangerObserver_(&zoneManager_), 
          cleanObserver_(&zoneManager_)
    {
    }

    void Initialize(int32_t x, int32_t y, Heading heading)
    {
        position_ = Position{x, y, heading};
        initialized_ = true;
    }

    void TurnRight()
    {
        if (!initialized_) {
            return;
        }
        int32_t newHeading = (static_cast<int32_t>(position_.heading) + 1) % 4;
        position_.heading = static_cast<Heading>(newHeading);
        NotifyPositionChanged();
    }

    void TurnLeft()
    {
        if (!initialized_) {
            return;
        }
        int32_t newHeading = (static_cast<int32_t>(position_.heading) + 3) % 4;
        position_.heading = static_cast<Heading>(newHeading);
        NotifyPositionChanged();
    }

    void TurnRound()
    {
        if (!initialized_) {
            return;
        }
        int32_t currentHeading = static_cast<int32_t>(position_.heading);
        int32_t newHeading = (currentHeading + 2) % 4;
        position_.heading = static_cast<Heading>(newHeading);
        NotifyPositionChanged();
    }

    void Forward()
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
        NotifyPositionChanged();
    }

    void Backward()
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
        NotifyPositionChanged();
    }

    void Forward(int32_t steps)
    {
        if (!initialized_ || steps <= 0) {
            return;
        }
        for (int32_t i = 0; i < steps; ++i) {
            Forward();
        }
    }

    void Backward(int32_t steps)
    {
        if (!initialized_ || steps <= 0) {
            return;
        }
        for (int32_t i = 0; i < steps; ++i) {
            Backward();
        }
    }

    Position GetPosition() const
    {
        if (!initialized_) {
            return Position{0, 0, Heading::North};
        }
        return position_;
    }

    bool SetDangerPoint(int32_t x, int32_t y)
    {
        return dangerObserver_.SetDangerPoint(x, y);
    }

    bool ClearDangerPoint()
    {
        return dangerObserver_.ClearDangerPoint();
    }

    bool SetCleanPoint(int32_t x, int32_t y)
    {
        return cleanObserver_.SetCleanPoint(x, y);
    }

    bool ClearCleanPoint()
    {
        return cleanObserver_.ClearCleanPoint();
    }

    void NotifyPositionChanged()
    {
        dangerObserver_.OnPositionChanged(position_);
        cleanObserver_.OnPositionChanged(position_);
    }

    void ExecuteCommand(const RepeatCommand& cmd)
    {
        if (cmd.repeatTimes <= 0) {
            return;
        }

        switch (cmd.type) {
            case CommandType::Forward:
                for (int32_t i = 0; i < cmd.repeatTimes; ++i) {
                    Forward();
                }
                break;
            case CommandType::Backward:
                for (int32_t i = 0; i < cmd.repeatTimes; ++i) {
                    Backward();
                }
                break;
            case CommandType::TurnRight:
                for (int32_t i = 0; i < cmd.repeatTimes; ++i) {
                    TurnRight();
                }
                break;
            case CommandType::TurnLeft:
                for (int32_t i = 0; i < cmd.repeatTimes; ++i) {
                    TurnLeft();
                }
                break;
            case CommandType::TurnRound:
                for (int32_t i = 0; i < cmd.repeatTimes; ++i) {
                    TurnRound();
                }
                break;
            case CommandType::Sequence:
                for (int32_t i = 0; i < cmd.repeatTimes; ++i) {
                    for (const auto& subCmd : cmd.subCommands) {
                        ExecuteCommand(subCmd);
                    }
                }
                break;
            default:
                break;
        }
    }
};

RobotExecutor::RobotExecutor()
    : impl_(std::make_unique<Impl>())
{
}

RobotExecutor::~RobotExecutor() = default;

void RobotExecutor::Initialize(int32_t x, int32_t y, Heading heading)
{
    impl_->Initialize(x, y, heading);
}

void RobotExecutor::TurnRight()
{
    impl_->TurnRight();
}

void RobotExecutor::TurnLeft()
{
    impl_->TurnLeft();
}

void RobotExecutor::TurnRound()
{
    impl_->TurnRound();
}

void RobotExecutor::Forward()
{
    impl_->Forward();
}

void RobotExecutor::Backward()
{
    impl_->Backward();
}

void RobotExecutor::Forward(int32_t steps)
{
    impl_->Forward(steps);
}

void RobotExecutor::Backward(int32_t steps)
{
    impl_->Backward(steps);
}

Position RobotExecutor::GetPosition() const
{
    return impl_->GetPosition();
}

bool RobotExecutor::SetDangerPoint(int32_t x, int32_t y)
{
    return impl_->SetDangerPoint(x, y);
}

bool RobotExecutor::ClearDangerPoint()
{
    return impl_->ClearDangerPoint();
}

bool RobotExecutor::SetCleanPoint(int32_t x, int32_t y)
{
    return impl_->SetCleanPoint(x, y);
}

bool RobotExecutor::ClearCleanPoint()
{
    return impl_->ClearCleanPoint();
}

void RobotExecutor::ExecuteCommand(const RepeatCommand& cmd)
{
    impl_->ExecuteCommand(cmd);
}