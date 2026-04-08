#include <cctest/cctest.h>
#include "executor/robot_executor.h"
#include "mcl/log/log.h"

FIXTURE(RobotExecutorTest) {
    BEFORE {
        MCL_LOG_INFO("TEST SETUP");
    }

    AFTER{
        MCL_LOG_INFO("TEST TEARDOWN");
    }

    /* 测试功能：支持初始化扫地机位置 */ 
    TEST("should initialize position correctly") {
        RobotExecutor executor;
        executor.Initialize(5, 10, Heading::East);
        auto pos = executor.GetPosition();
        ASSERT_EQ(5, pos.x);
        ASSERT_EQ(10, pos.y);
        ASSERT_EQ(Heading::East, pos.heading);
    }

    TEST("should allow re-initialization") {
        RobotExecutor executor;
        executor.Initialize(1, 2, Heading::North);
        executor.Initialize(3, 4, Heading::South);
        auto pos = executor.GetPosition();
        ASSERT_EQ(3, pos.x);
        ASSERT_EQ(4, pos.y);
        ASSERT_EQ(Heading::South, pos.heading);
    }

    TEST("should return default position when not initialized") {
        RobotExecutor executor;
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
        ASSERT_EQ(Heading::North, pos.heading);
    }

    /* 测试功能：支持向扫地机发送左转和右转指令 */ 
    TEST("should turn right from north to east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.TurnRight();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::East, pos.heading);
    }

    TEST("should turn left from north to west") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.TurnLeft();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::West, pos.heading);
    }

    TEST("should return to original heading after 4 right turns") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::North, pos.heading);
    }

    TEST("should return to original heading after 4 left turns") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.TurnLeft();
        executor.TurnLeft();
        executor.TurnLeft();
        executor.TurnLeft();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::East, pos.heading);
    }

    TEST("should not change heading when turning right without initialization") {
        RobotExecutor executor;
        executor.TurnRight();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
        ASSERT_EQ(Heading::North, pos.heading);
    }
};
