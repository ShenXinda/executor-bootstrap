## Why

在已实现的RobotExecutor组件基础上，扩展移动指令功能，实现前进和后退动作，使机器人能够在二维平面上移动。这是扫地机器人控制系统的重要扩展，支持完整的运动控制。

## What Changes

- 新增Forward接口：沿当前朝向前进一步，x或y坐标根据朝向变化
- 新增Backward接口：沿当前朝向后退一步，x或y坐标根据朝向变化
- 坐标轴定义：x左为西，x右为东；y上为北，y下为南
- forward/backward仅改变位置，不改变朝向

## Capabilities

### New Capabilities

- **robot-movement**: 前进/后退移动功能
  - forward: 朝向方向移动一步
  - backward: 朝向相反方向移动一步

### Modified Capabilities

- **robot-executor**: 扩展现有RobotExecutor组件
  - 新增Forward()方法
  - 新增Backward()方法

## Impact

- 修改src/robot_executor.cpp，添加Forward/Backward实现
- 修改include/executor/robot_executor.h，添加方法声明
- 扩展test/robot_executor_test.cpp，添加移动相关测试用例