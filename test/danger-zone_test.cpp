#include <cctest/cctest.h>
#include "executor/robot_executor.h"
#include "executor/danger_zone_observer.h"
#include "mcl/log/log.h"
#include "alert/alert.h"
#include "mockcpp/mockcpp.hpp"

using namespace mockcpp;

FIXTURE(DangerZoneTest) {
    BEFORE {
        MCL_LOG_INFO("DANGER ZONE TEST SETUP");
    }

    AFTER{
        MCL_LOG_INFO("DANGER ZONE TEST TEARDOWN");
        GlobalMockObject::verify();
    }

    TEST("should set danger point and trigger alert when reached") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(5), eq(0));
        RobotExecutor executor;
        DangerZoneObserver observer;
        observer.SetDangerPoint(5, 0);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::East);
        executor.Forward();
        executor.Forward();
        executor.Forward();
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when forward to danger point") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(1));
        RobotExecutor executor;
        DangerZoneObserver observer;
        observer.SetDangerPoint(0, 1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when backward to danger point") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(-1));
        RobotExecutor executor;
        DangerZoneObserver observer;
        observer.SetDangerPoint(0, -1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Backward();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when turn right at danger point") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(0));
        RobotExecutor executor;
        DangerZoneObserver observer;
        executor.RegisterObserver(&observer);
        executor.Initialize(0, -1, Heading::North);
        executor.Forward();
        observer.SetDangerPoint(0, 0);
        executor.TurnRight();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when turn left at danger point") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(0));
        RobotExecutor executor;
        DangerZoneObserver observer;
        executor.RegisterObserver(&observer);
        executor.Initialize(0, -1, Heading::North);
        executor.Forward();
        observer.SetDangerPoint(0, 0);
        executor.TurnLeft();
        GlobalMockObject::verify();
    }

    TEST("should trigger alert repeatedly at same danger point") {
        MOCKER(alert).expects(exactly(4)).with(eq(IN_DANGEROUS), eq(0), eq(1));
        RobotExecutor executor;
        DangerZoneObserver observer;
        observer.SetDangerPoint(0, 1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        executor.Backward();
        executor.Forward();
        executor.TurnLeft();
        executor.TurnRight();
        GlobalMockObject::verify();
    }

    TEST("should not trigger alert when danger point not set") {
        MOCKER(alert).expects(never());
        RobotExecutor executor;
        DangerZoneObserver observer;
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
        GlobalMockObject::verify();
    }

    TEST("should not trigger alert when moving away from danger point") {
        MOCKER(alert).expects(never());
        RobotExecutor executor;
        DangerZoneObserver observer;
        observer.SetDangerPoint(5, 5);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        auto pos = executor.GetPosition();
        ASSERT_EQ(0, pos.x);
        ASSERT_EQ(1, pos.y);
        GlobalMockObject::verify();
    }
};