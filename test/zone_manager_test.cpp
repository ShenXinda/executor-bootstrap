#include <cctest/cctest.h>
#include "executor/robot_executor.h"
#include "mcl/log/log.h"
#include "alert/alert.h"
#include "clean/clean.h"
#include "mockcpp/mockcpp.hpp"

using namespace mockcpp;

FIXTURE(ZoneManagerTest) {
    BEFORE {
        MCL_LOG_INFO("ZONE MANAGER TEST SETUP");
    }

    AFTER{
        MCL_LOG_INFO("ZONE MANAGER TEST TEARDOWN");
        GlobalMockObject::verify();
    }

    TEST("should set danger point via RobotExecutor") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(5), eq(3));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetDangerPoint(5, 3);
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should set clean point via RobotExecutor") {
        MOCKER(clean).expects(once()).with(eq(2), eq(1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(2, 1);
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should clear danger point via RobotExecutor") {
        MOCKER(alert).expects(never());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetDangerPoint(5, 3);
        executor.ClearDangerPoint();
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.TurnRight();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should clear clean point via RobotExecutor") {
        MOCKER(clean).expects(never());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(2, 1);
        executor.ClearCleanPoint();
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should set danger and clean via RobotExecutor") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(1), eq(0));
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetDangerPoint(1, 0);
        executor.SetCleanPoint(0, 1);
        executor.Forward();
        executor.TurnLeft();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when robot reaches danger point") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(1), eq(0));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::East);
        executor.SetDangerPoint(1, 0);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when robot reaches danger point from north") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetDangerPoint(0, 1);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger clean when robot reaches clean point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.SetCleanPoint(0, 1);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should not trigger when danger point not set") {
        MOCKER(alert).expects(never());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should not trigger when clean point not set") {
        MOCKER(clean).expects(never());
        RobotExecutor executor;
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        GlobalMockObject::verify();
    }
};