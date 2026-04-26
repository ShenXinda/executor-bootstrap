## Why

当前RobotExecutor仅支持单步动作指令（如forward、backward、turnRight等），无法处理Controller发来的复合动作指令。需求7要求Executor支持重复执行和指令序列两种复合指令，并支持任意嵌套。

## What Changes

1. 新增重复执行指令解析和执行：
   - `repeat <command> <n>` - 将指定动作重复执行n次
   - 支持任意单步指令的重复（如 repeat forward 5）

2. 新增指令序列执行：
   - `{command1, command2, ...}` - 按顺序执行一组指令
   - 支持任意数量和类型的指令组合

3. 支持指令嵌套：
   - repeat可以嵌套command列表，command列表也可以嵌套repeat
   - 支持多层嵌套，如 `{repeat forward 3, repeat turnRight 2}`

## Capabilities

### New Capabilities
- `executor-repeat-command`: 支持repeat n times指令
- `executor-command-sequence`: 支持指令序列 {cmd1, cmd2, ...}
- `executor-nested-commands`: 支持任意指令嵌套

### Modified Capabilities
- `robot-executor`: 扩展支持复合动作指令

## Impact

- 头文件：include/executor/robot_executor.h 新增方法声明
- 实现：src/robot_executor.cpp 新增复合指令解析和执行逻辑
- 测试：新增复合指令测试用例