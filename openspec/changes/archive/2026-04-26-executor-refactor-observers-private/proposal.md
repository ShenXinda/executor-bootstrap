## Why

当前RobotExecutor的内部组件（PositionObserver及其子类、ZoneManager）对外部暴露，违反接口封装原则。所有对外接口应集中在RobotExecutor类中提供，隐藏实现细节。

## What Changes

1. RobotExecutor类新增4个接口方法：
   - `bool SetDangerPoint(int32_t x, int32_t y)` - 设置危险点
   - `bool ClearDangerPoint()` - 清除危险点
   - `bool SetCleanPoint(int32_t x, int32_t y)` - 设置清扫点
   - `bool ClearCleanPoint()` - 清除清扫点

2. include目录下新增private目录，将以下头文件移动到private目录：
   - clean_zone_observer.h
   - danger_zone_observer.h
   - position_observer.h
   - zone_manager.h

3. 更新robot_executor.h，移除或隐藏对这些实现类的直接引用

## Capabilities

### New Capabilities
- `executor-danger-point-management`: 通过RobotExecutor接口管理危险点
- `executor-clean-point-management`: 通过RobotExecutor接口管理清扫点

### Modified Capabilities
- `robot-executor`: 扩展接口能力，新增危险点/清扫点管理接口

## Impact

- 头文件：include/executor/robot_executor.h 新增4个方法声明
- 头文件：include/executor/private/ 目录及4个头文件
- 实现：src/robot_executor.cpp 无变化（方法已实现）
- 测试：现有测试应继续通过（API已在RobotExecutor中）