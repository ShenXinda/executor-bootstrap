#include <cctest/cctest.h>
#include "executor/robot_executor.h"
#include "mcl/log/log.h"
#include "clean/clean.h"
#include "alert/alert.h"
#include "mockcpp/mockcpp.hpp"

using namespace mockcpp;

FIXTURE(CleanZoneTest) {
    BEFORE {
        MCL_LOG_INFO("CLEAN ZONE TEST SETUP");
    }

    AFTER{
        MCL_LOG_INFO("CLEAN ZONE TEST TEARDOWN");
        GlobalMockObject::verify();
    }

    TEST("should set clean point and trigger clean when reached") {
        MOCKER(clean).expects(once()).with(eq(5), eq(0));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.SetCleanPoint(5, 0);
        executor.Forward();
        executor.Forward();
        executor.Forward();
        executor.Forward();
        executor.Forward();
        executor.TurnLeft();
        executor.TurnRight();
        GlobalMockObject::verify();
    }

    TEST("should trigger clean when forward to clean point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, 1);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger clean when backward to clean point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(-1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, -1);
        executor.Backward();
        GlobalMockObject::verify();
    }

    TEST("should not trigger clean again when revisiting same point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, 1);
        executor.Forward();
        executor.Backward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger clean again after re-initialization") {
        MOCKER(clean).expects(exactly(2)).with(any(), any());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, 1);
        executor.Forward();
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, 1);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should not trigger clean when clean point not set") {
        MOCKER(clean).expects(never());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
        GlobalMockObject::verify();
    }

    TEST("should not trigger clean when moving away from clean point") {
        MOCKER(clean).expects(never());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(5, 5);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
        GlobalMockObject::verify();
    }

    TEST("should trigger clean and alert at different points") {
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(2));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, 1);
        executor.SetDangerPoint(0, 2);
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should not set multiple clean zone") {
        MOCKER(clean).expects(never());
        RobotExecutor executor;
        executor.SetCleanPoint(0, 1);
        executor.SetCleanPoint(1, 0);
        executor.Initialize(0, 0, Heading::East);
        executor.Forward();
        GlobalMockObject::verify();
    }
};