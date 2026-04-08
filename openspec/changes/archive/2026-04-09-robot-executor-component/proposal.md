## Why

需要一个Executor组件来控制扫地机器人的位置和朝向，实现初始化接口和动作指令执行功能。这是扫地机器人控制系统的核心组件，负责机器人的位置管理和动作执行。

## What Changes

- 新增Executor组件，提供扫地机初始化接口，设置位置(x, y)和朝向(heading)
- 新增Executor组件，提供动作指令执行接口(turn right, turn left)
- 新增Executor组件查询接口，获取当前坐标位置和朝向
- 未初始化时默认返回(0, 0, 朝向北)
- 提供单元测试用例验证功能

## Capabilities

### New Capabilities

- **robot-executor**: Executor组件，负责扫地机位置管理和动作执行
  - 初始化接口：设置位置(x, y, heading)
  - 动作执行：turn right(右转90度)，turn left(左转90度)
  - 状态查询：获取当前坐标和朝向
  - 默认状态：(0, 0, 朝向北)

### Modified Capabilities

- 无

## Impact

- 新增src/Executor组件相关源文件
- 新增include/Executor组件头文件
- 新增test/Executor测试用例
- 需要Controller组件集成(后续实现)
