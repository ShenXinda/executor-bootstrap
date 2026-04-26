## Why

当前RobotExecutor仅支持单步移动（Forward/Backward），无法执行Controller发来的多步移动指令（如"forward 5 step"）。同时缺少旋转180度的指令（turn round）。需要扩展移动指令以支持更丰富的控制命令，并确保路径上的告警和清扫活动能正确触发。

## What Changes

1. 新增 `TurnRound()` 方法 - 执行180度旋转（右转两次），位置不变
2. 新增 `Forward(int32_t steps)` 方法 - 沿当前朝向前进n步
3. 新增 `Backward(int32_t steps)` 方法 - 沿当前朝向后退n步
4. 修改移动逻辑 - 支持多步移动过程中触发告警和清扫

## Capabilities

### New Capabilities
- **multi-step-move**: 支持多步移动指令（forward n step, backward n step）和旋转180度指令（turn round）

### Modified Capabilities
- **robot-executor**: 扩展forward/backward方法签名，增加steps参数

## Impact

- 修改 `include/executor/robot_executor.h` - 新增方法签名
- 修改 `src/robot_executor.cpp` - 实现多步移动逻辑
- 修改现有测试以适配新接口
- 测试覆盖多步移动触发告警/清扫的场景