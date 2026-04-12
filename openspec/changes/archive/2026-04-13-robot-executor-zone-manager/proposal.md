## 需求背景

当前RobotExecutor的告警点（DangerZoneObserver）和清扫点（CleanZoneObserver）各自独立管理资源，无法共享16个槽位的资源限制。同时缺少取消已配置坐标点的接口和清扫后自动回收槽位的机制，导致资源利用率低且无法动态管理坐标点。

### 当前问题

1. **资源无法共享** - DangerZoneObserver和CleanZoneObserver各维护一个点，无法共享16个槽位
2. **无法配置/取消** - 没有提供取消已配置坐标点的接口
3. **无法自动回收** - 清扫后没有自动回收机制
4. **扩展性差** - 每个Observer只能存一个点

## 需求目标

1. **保留现有Observer接口** - 旧代码无需修改
2. **统一16个资源槽位** - 告警点和清扫点共享
3. **支持配置/取消** - Config可添加和移除坐标点
4. **自动回收** - 清扫后自动释放槽位

## 变更内容

1. 新增 `ZoneManager` 类 - 统一管理16个共享槽位，支持告警点和清扫点
2. 新增 `ZoneType` 枚举 - 区分告警（Alert）和清扫（Clean）类型
3. 新增 `ZoneSlot` 结构 - 存储坐标点信息（x, y, type, active）
4. 新增 `AddPoint` 方法 - 添加坐标点到槽位
5. 新增 `RemovePoint` 方法 - 取消已配置的坐标点
6. 新增 `OnCleaned` 方法 - 清扫后自动回收槽位
7. 保持现有Observer接口兼容 - DangerZoneObserver和CleanZoneObserver可继续使用

## 功能范围

### 新增能力

- **zone-manager**：统一管理16个共享槽位的坐标点，支持告警点和清扫点的添加、取消和自动回收

### 修改能力

- 无 - 本次为新增能力，不修改现有需求

## 影响范围

- 新增文件：`include/executor/zone_manager.h`、`src/executor/zone_manager.cpp`
- 修改文件：`include/executor/robot_executor.h`、`src/executor/robot_executor.cpp`、`include/executor/danger_zone_observer.h`、`src/executor/danger_zone_observer.cpp`、`include/executor/clean_zone_observer.h`、`src/executor/clean_zone_observer.cpp`
- 测试文件：`test/zone_manager_test.cpp`