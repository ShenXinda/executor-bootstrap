#include <cctest/cctest.h>
#include "executor/zone_manager.h"
#include "executor/robot_executor.h"
#include "executor/danger_zone_observer.h"
#include "executor/clean_zone_observer.h"
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

    TEST("should add alert point successfully") {
        ZoneManager zoneMgr;
        bool result = zoneMgr.AddPoint(ZoneType::Alert, 5, 3);
        ASSERT_TRUE(result);
        ASSERT_EQ(15, zoneMgr.GetFreeCount());
        ASSERT_EQ(1, zoneMgr.GetAlertPointCount());
    }

    TEST("should add clean point successfully") {
        ZoneManager zoneMgr;
        bool result = zoneMgr.AddPoint(ZoneType::Clean, 2, 1);
        ASSERT_TRUE(result);
        ASSERT_EQ(15, zoneMgr.GetFreeCount());
        ASSERT_EQ(1, zoneMgr.GetCleanPointCount());
    }

    TEST("should not add duplicate point") {
        ZoneManager zoneMgr;
        bool result1 = zoneMgr.AddPoint(ZoneType::Alert, 5, 3);
        ASSERT_TRUE(result1);
        bool result2 = zoneMgr.AddPoint(ZoneType::Alert, 5, 3);
        ASSERT_FALSE(result2);
    }

    TEST("should not add when slots are full") {
        ZoneManager zoneMgr;
        for (int i = 0; i < 16; ++i) {
            zoneMgr.AddPoint(ZoneType::Alert, i, 0);
        }
        bool result = zoneMgr.AddPoint(ZoneType::Alert, 100, 100);
        ASSERT_FALSE(result);
    }

    TEST("should remove point successfully") {
        ZoneManager zoneMgr;
        zoneMgr.AddPoint(ZoneType::Alert, 5, 3);
        bool result = zoneMgr.RemovePoint(5, 3);
        ASSERT_TRUE(result);
        ASSERT_EQ(16, zoneMgr.GetFreeCount());
    }

    TEST("should return false when removing non-existent point") {
        ZoneManager zoneMgr;
        bool result = zoneMgr.RemovePoint(5, 3);
        ASSERT_FALSE(result);
    }

    TEST("should share slots between alert and clean points") {
        ZoneManager zoneMgr;
        zoneMgr.AddPoint(ZoneType::Alert, 1, 1);
        zoneMgr.AddPoint(ZoneType::Clean, 2, 2);
        zoneMgr.AddPoint(ZoneType::Alert, 3, 3);
        ASSERT_EQ(13, zoneMgr.GetFreeCount());
        ASSERT_EQ(2, zoneMgr.GetAlertPointCount());
        ASSERT_EQ(1, zoneMgr.GetCleanPointCount());
    }

    TEST("should trigger clean and auto-recycle when position matches") {
        MOCKER(clean).expects(once()).with(eq(2), eq(1));
        ZoneManager zoneMgr;
        zoneMgr.AddPoint(ZoneType::Clean, 2, 1);
        Position pos = {2, 1, Heading::North};
        zoneMgr.OnPositionChanged(pos);
        ASSERT_EQ(16, zoneMgr.GetFreeCount());
        GlobalMockObject::verify();
    }

    TEST("should trigger alert when position matches") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(5), eq(3));
        ZoneManager zoneMgr;
        zoneMgr.AddPoint(ZoneType::Alert, 5, 3);
        Position pos = {5, 3, Heading::North};
        zoneMgr.OnPositionChanged(pos);
        GlobalMockObject::verify();
    }

    TEST("should recycle slot after clean") {
        ZoneManager zoneMgr;
        zoneMgr.AddPoint(ZoneType::Clean, 2, 1);
        Position pos = {2, 1, Heading::North};
        zoneMgr.OnPositionChanged(pos);
        bool result = zoneMgr.AddPoint(ZoneType::Clean, 3, 3);
        ASSERT_TRUE(result);
    }

    TEST("should work with DangerZoneObserver") {
        ZoneManager zoneMgr;
        DangerZoneObserver observer(&zoneMgr);
        bool result = observer.SetDangerPoint(5, 3);
        ASSERT_TRUE(result);
        ASSERT_EQ(1, zoneMgr.GetAlertPointCount());
    }

    TEST("should work with CleanZoneObserver") {
        ZoneManager zoneMgr;
        CleanZoneObserver observer(&zoneMgr);
        bool result = observer.SetCleanPoint(2, 1);
        ASSERT_TRUE(result);
        ASSERT_EQ(1, zoneMgr.GetCleanPointCount());
    }

    TEST("should not set multiple danger points") {
        ZoneManager zoneMgr;
        DangerZoneObserver observer(&zoneMgr);
        bool result1 = observer.SetDangerPoint(5, 3);
        ASSERT_TRUE(result1);
        bool result2 = observer.SetDangerPoint(6, 4);
        ASSERT_FALSE(result2);
    }

    TEST("should not set multiple clean points") {
        ZoneManager zoneMgr;
        CleanZoneObserver observer(&zoneMgr);
        bool result1 = observer.SetCleanPoint(2, 1);
        ASSERT_TRUE(result1);
        bool result2 = observer.SetCleanPoint(3, 4);
        ASSERT_FALSE(result2);
    }

    TEST("should clear danger point") {
        ZoneManager zoneMgr;
        DangerZoneObserver observer(&zoneMgr);
        observer.SetDangerPoint(5, 3);
        ASSERT_EQ(1, zoneMgr.GetAlertPointCount());
        bool result = observer.ClearDangerPoint();
        ASSERT_TRUE(result);
        ASSERT_EQ(0, zoneMgr.GetAlertPointCount());
    }

    TEST("should clear clean point") {
        ZoneManager zoneMgr;
        CleanZoneObserver observer(&zoneMgr);
        observer.SetCleanPoint(2, 1);
        ASSERT_EQ(1, zoneMgr.GetCleanPointCount());
        bool result = observer.ClearCleanPoint();
        ASSERT_TRUE(result);
        ASSERT_EQ(0, zoneMgr.GetCleanPointCount());
    }

    TEST("should work with RobotExecutor via observers") {
        ZoneManager zoneMgr;
        RobotExecutor executor;
        DangerZoneObserver dangerObserver(&zoneMgr);
        CleanZoneObserver cleanObserver(&zoneMgr);

        dangerObserver.SetDangerPoint(5, 3);
        cleanObserver.SetCleanPoint(2, 1);

        executor.RegisterObserver(&dangerObserver);
        executor.RegisterObserver(&cleanObserver);

        ASSERT_EQ(14, zoneMgr.GetFreeCount());
        ASSERT_EQ(1, zoneMgr.GetAlertPointCount());
        ASSERT_EQ(1, zoneMgr.GetCleanPointCount());
    }

    TEST("should auto-recycle when robot reaches clean point") {
        MOCKER(clean).expects(once()).with(eq(0), eq(1));
        ZoneManager zoneMgr;
        RobotExecutor executor;
        CleanZoneObserver cleanObserver(&zoneMgr);

        cleanObserver.SetCleanPoint(0, 1);
        executor.RegisterObserver(&cleanObserver);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();

        GlobalMockObject::verify();
        ASSERT_EQ(16, zoneMgr.GetFreeCount());
    }

    TEST("should trigger alert when robot reaches danger point") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(1), eq(0));
        ZoneManager zoneMgr;
        RobotExecutor executor;
        DangerZoneObserver dangerObserver(&zoneMgr);

        dangerObserver.SetDangerPoint(1, 0);
        executor.RegisterObserver(&dangerObserver);
        executor.Initialize(0, 0, Heading::East);
        executor.Forward();

        GlobalMockObject::verify();
    }

    TEST("should trigger alert when robot reaches danger point from north") {
        MOCKER(alert).expects(once()).with(eq(IN_DANGEROUS), eq(0), eq(1));
        ZoneManager zoneMgr;
        RobotExecutor executor;
        DangerZoneObserver dangerObserver(&zoneMgr);

        dangerObserver.SetDangerPoint(0, 1);
        executor.RegisterObserver(&dangerObserver);
        executor.Initialize(0, 0, Heading::North);
        executor.Forward();

        GlobalMockObject::verify();
    }
};