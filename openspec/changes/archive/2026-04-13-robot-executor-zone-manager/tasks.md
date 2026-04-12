## 1. 创建ZoneManager类

- [x] 1.1 创建 `include/executor/zone_manager.h` - 定义ZoneType枚举、ZoneSlot结构、ZoneManager类，包含AddPoint、RemovePoint、OnPositionChanged、OnCleaned、GetFreeCount、GetAlertPointCount、GetCleanPointCount方法
- [x] 1.2 创建 `src/zone_manager.cpp` - 实现ZoneManager方法，使用std::array<ZoneSlot, 16>存储槽位
- [x] 1.3 验证ZoneManager编译正确

## 2. 集成ZoneManager到RobotExecutor

- [x] 2.1 修改 `include/executor/robot_executor.h` - 添加ZoneManager指针成员，添加SetDangerPoint/SetCleanPoint返回值，添加RemoveDangerPoint/RemoveCleanPoint方法
- [x] 2.2 修改 `src/robot_executor.cpp` - 实现ZoneManager集成，更新SetDangerPoint使用zoneManager_->AddPoint
- [x] 2.3 验证RobotExecutor编译正确

## 3. 更新Observer类

- [x] 3.1 修改 `include/executor/danger_zone_observer.h` - 更新使用ZoneManager存储
- [x] 3.2 修改 `src/danger_zone_observer.cpp` - 实现委托到ZoneManager
- [x] 3.3 修改 `include/executor/clean_zone_observer.h` - 更新使用ZoneManager存储
- [x] 3.4 修改 `src/clean_zone_observer.cpp` - 实现委托到ZoneManager

## 4. 添加单元测试

- [x] 4.1 创建 `test/zone_manager_test.cpp` - 测试AddPoint、RemovePoint、GetFreeCount、清扫自动回收
- [x] 4.2 运行测试并验证全部通过

## 5. 构建与验证

- [x] 5.1 运行完整构建 `./ccup.sh -ub`
- [x] 5.2 运行测试 `./ccup.sh -t`
- [x] 5.3 验证实现匹配design.md和specs/zone-manager/spec.md