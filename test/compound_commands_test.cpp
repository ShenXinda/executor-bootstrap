#include <cctest/cctest.h>
#include "executor/robot_executor.h"
#include "mcl/log/log.h"

FIXTURE(CompoundCommandsTest) {
    BEFORE {
        MCL_LOG_INFO("COMPOUND COMMANDS TEST SETUP");
    }

    AFTER{
        MCL_LOG_INFO("COMPOUND COMMANDS TEST TEARDOWN");
    }

    TEST("should repeat forward 3 times") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand cmd{CommandType::Forward, 3, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(3, pos.y);
    }

    TEST("should repeat forward 5 times east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        RepeatCommand cmd{CommandType::Forward, 5, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(5, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should repeat backward 2 times") {
        RobotExecutor executor;
        executor.Initialize(0, 3, Heading::North);
        RepeatCommand cmd{CommandType::Backward, 2, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
    }

    TEST("should repeat turn right 2 times") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand cmd{CommandType::TurnRight, 2, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::South, pos.heading);
    }

    TEST("should repeat turn left 3 times from north to east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand cmd{CommandType::TurnLeft, 3, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::East, pos.heading);
    }

    TEST("should not repeat when times is 0") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand cmd{CommandType::Forward, 0, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should not repeat when times is negative") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand cmd{CommandType::Forward, -1, {}};
        executor.ExecuteCommand(cmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should execute sequence forward right forward") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand cmd1{CommandType::Forward, 1, {}};
        RepeatCommand cmd2{CommandType::TurnRight, 1, {}};
        RepeatCommand cmd3{CommandType::Forward, 1, {}};
        RepeatCommand sequence{CommandType::Sequence, 1, {cmd1, cmd2, cmd3}};
        executor.ExecuteCommand(sequence);
        auto pos = executor.GetPosition();
        ASSERT_EQ(1, pos.x);
        ASSERT_EQ(1, pos.y);
        ASSERT_EQ(Heading::East, pos.heading);
    }

    TEST("should handle nested commands repeat in sequence") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand repeatCmd{CommandType::Forward, 2, {}};
        RepeatCommand sequence{CommandType::Sequence, 1, {repeatCmd}};
        executor.ExecuteCommand(sequence);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(2, pos.y);
    }

    TEST("should handle sequence in repeat") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        RepeatCommand subCmd{CommandType::Forward, 1, {}};
        RepeatCommand repeatCmd{CommandType::Sequence, 2, {subCmd}};
        executor.ExecuteCommand(repeatCmd);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(2, pos.y);
    }
};