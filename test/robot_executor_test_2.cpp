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

    /* 测试功能：支持扫地机器人前进和后退一步 */ 
    TEST("should move forward north") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
    }

    TEST("should move forward east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(1, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should move forward south") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::South);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(-1, pos.y);
    }

    TEST("should move forward west") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::West);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(-1, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should move backward north") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Backward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(-1, pos.y);
    }

    TEST("should move backward east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.Backward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(-1, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should move backward south") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::South);
        executor.Backward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
    }

    TEST("should move backward west") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::West);
        executor.Backward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(1, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should not move when forward without initialization") {
        RobotExecutor executor;
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should not move when backward without initialization") {
        RobotExecutor executor;
        executor.Backward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }
};
