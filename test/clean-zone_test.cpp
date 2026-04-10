#include <cctest/cctest.h>
#include "executor/robot_executor.h"
#include "executor/clean_zone_observer.h"
#include "executor/danger_zone_observer.h"
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
        CleanZoneObserver observer;
        observer.SetCleanPoint(5, 0);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::East);
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
        CleanZoneObserver observer;
        observer.SetCleanPoint(0, 1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger clean when backward to clean point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(-1));
        RobotExecutor executor;
        CleanZoneObserver observer;
        observer.SetCleanPoint(0, -1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Backward();
        GlobalMockObject::verify();
    }

    TEST("should not trigger clean again when revisiting same point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        RobotExecutor executor;
        CleanZoneObserver observer;
        observer.SetCleanPoint(0, 1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        executor.Backward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should trigger clean again after re-initialization") {
        MOCKER(clean).expects(exactly(2)).with(any(), any());
        RobotExecutor executor;
        CleanZoneObserver observer;
        observer.SetCleanPoint(0, 1);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        observer.Reset();
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should not trigger clean when clean point not set") {
        MOCKER(clean).expects(never());
        RobotExecutor executor;
        CleanZoneObserver observer;
        executor.RegisterObserver(&observer);
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
        CleanZoneObserver observer;
        observer.SetCleanPoint(5, 5);
        executor.RegisterObserver(&observer);
        executor.Initialize(0, 0, Heading::North);
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
        CleanZoneObserver cleanObserver;
        DangerZoneObserver dangerObserver;
        cleanObserver.SetCleanPoint(0, 1);
        dangerObserver.SetDangerPoint(0, 2);
        executor.RegisterObserver(&cleanObserver);
        executor.RegisterObserver(&dangerObserver);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should allow multiple clean observers") {
        MOCKER(clean).expects(exactly(2)).with(any(), any());
        RobotExecutor executor;
        CleanZoneObserver cleanObserver1;
        CleanZoneObserver cleanObserver2;
        cleanObserver1.SetCleanPoint(0, 1);
        cleanObserver2.SetCleanPoint(0, 2);
        executor.RegisterObserver(&cleanObserver1);
        executor.RegisterObserver(&cleanObserver2);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should allow multiple danger observers") {
        MOCKER(alert).expects(exactly(2)).with(any(), any());
        RobotExecutor executor;
        DangerZoneObserver dangerObserver1;
        DangerZoneObserver dangerObserver2;
        dangerObserver1.SetDangerPoint(0, 1);
        dangerObserver2.SetDangerPoint(0, 2);
        executor.RegisterObserver(&dangerObserver1);
        executor.RegisterObserver(&dangerObserver2);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }

    TEST("should allow mixed clean and danger observers") {
        MOCKER(clean).expects(once()).with(any(), any());
        MOCKER(alert).expects(once()).with(any(), any());
        RobotExecutor executor;
        CleanZoneObserver cleanObserver;
        DangerZoneObserver dangerObserver;
        cleanObserver.SetCleanPoint(0, 1);
        dangerObserver.SetDangerPoint(0, 2);
        executor.RegisterObserver(&cleanObserver);
        executor.RegisterObserver(&dangerObserver);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();
        executor.Forward();
        GlobalMockObject::verify();
    }
};