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

    /* 测试功能：旋转180度 */
    TEST("should turn round from north to south") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.TurnRound();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::South, pos.heading);
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should turn round from east to west") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.TurnRound();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::West, pos.heading);
    }

    TEST("should turn round from south to north") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::South);
        executor.TurnRound();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::North, pos.heading);
    }

    TEST("should turn round from west to east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::West);
        executor.TurnRound();
        auto pos = executor.GetPosition();
        ASSERT_EQ(Heading::East, pos.heading);
    }

    /* 测试功能：多步移动 */
    TEST("should move forward 3 steps north") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward(3);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(3, pos.y);
    }

    TEST("should move forward 5 steps east") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.Forward(5);
        auto pos = executor.GetPosition();
        ASSERT_EQ(5, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should move backward 2 steps north") {
        RobotExecutor executor;
        executor.Initialize(0, 3, Heading::North);
        executor.Backward(2);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
    }

    TEST("should move backward 3 steps east") {
        RobotExecutor executor;
        executor.Initialize(5, 0, Heading::East);
        executor.Backward(3);
        auto pos = executor.GetPosition();
        ASSERT_EQ(2, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    /* 测试功能：边界条件 */
    TEST("should not move when forward with 0 steps") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward(0);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should not move when forward with negative steps") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward(-1);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should not move when backward with 0 steps") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Backward(0);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should not move when backward with negative steps") {
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Backward(-1);
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(0, pos.y);
    }

    TEST("should turn round not change position") {
        RobotExecutor executor;
        executor.Initialize(5, 5, Heading::North);
        executor.TurnRound();
        auto pos = executor.GetPosition();
        ASSERT_EQ(5, pos.x);
        ASSERT_EQ(5, pos.y);
    }
};
