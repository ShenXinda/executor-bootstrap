## Why

在RobotExecutor组件已实现移动功能的基础上，增加危险坐标点告警功能。当扫地机移动到由Config组件设置的危险坐标点时，需要触发Alert组件的告警。这是安全监控的重要功能，确保机器人不会进入危险区域。

## What Changes

- 新增SetDangerPoint接口：Config组件设置危险坐标点(x1, y1)
- 新增危险坐标检测逻辑：在每次移动前检查目标坐标是否为危险点
- 新增告警触发：当移动到危险坐标时，调用alert(IN_DANGEROUS, x, y)触发告警
- 支持重复触发：同一点反复经过可重复告警

## Capabilities

### New Capabilities

- **danger-zone-alert**: 危险坐标告警功能
  - 设置危险坐标点接口
  - 移动时检测危险坐标
  - 触发Alert组件告警

### Modified Capabilities

- **robot-executor**: 扩展现有RobotExecutor组件
  - 新增SetDangerPoint()方法
  - 修改Forward/Backward/TurnRight/TurnLeft在移动后检测危险点

## Impact

- 修改src/robot_executor.cpp，添加危险坐标检测和告警触发
- 修改include/executor/robot_executor.h，添加SetDangerPoint声明
- 修改test/robot_executor_test.cc，添加危险坐标测试用例
- 依赖alert-intf组件的alert接口