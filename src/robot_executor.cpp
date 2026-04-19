#include "executor/robot_executor.h"
#include "executor/robot_common_type.h"

class RobotExecutor::Impl
{
private:
    Position position_;
    bool initialized_ {false};
    std::vector<PositionObserver*> observers_;

public:
    Impl()
        : initialized_(false)
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

    void RegisterObserver(PositionObserver* observer)
    {
        observers_.push_back(observer);
    }

    void UnregisterObserver(PositionObserver* observer)
    {
        for (auto it = observers_.begin(); it != observers_.end(); ++it) {
            if (*it == observer) {
                observers_.erase(it);
                break;
            }
        }
    }

private:
    void NotifyPositionChanged()
    {
        for (auto* observer : observers_) {
            observer->OnPositionChanged(position_);
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

void RobotExecutor::RegisterObserver(PositionObserver* observer)
{
    impl_->RegisterObserver(observer);
}

void RobotExecutor::UnregisterObserver(PositionObserver* observer)
{
    impl_->UnregisterObserver(observer);
}