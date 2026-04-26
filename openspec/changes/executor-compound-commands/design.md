## Context

RobotExecutor目前支持单步动作指令的执行（forward、backward、turnRight、turnLeft、turnRound）。Controller组件可能发送复合动作指令如"repeat forward 5"或"{forward, turnRight, forward}"。

复合指令格式：
- repeat命令：repeat <command> <n>
- 命令序列：{command1, command2, ...}
- 嵌套支持：repeat和序列可以互相嵌套

## Goals / Non-Goals

**Goals:**
- 实现repeat命令：重复执行单步指令n次
- 实现命令序列：按顺序执行多个命令
- 支持任意嵌套：repeat嵌套序列，序列嵌套repeat，以及多层嵌套

**Non-Goals:**
- 不解析完整的命令行语法（由Controller解析）
- 不处理条件分支或循环控制
- 不支持变量或宏定义

## Decisions

### D1: 复合指令的数据结构
**选择**: 使用变体（variant）或字符串标识来表示不同类型的指令
**理由**: 
- 简单实现：executor只需执行，不需要复杂解析
- 灵活性：支持任意嵌套
- 组合模式可递归

### D2: 执行方式
**选择**: 递归执行
**理由**:
- 嵌套需要递归处理
- 保持代码简洁

### D3: 接口设计
**选择**: 提供复合执行方法，不暴露给Controller的解析结果
**理由**:
- 隔离关注点：Controller负责解析，Executor负责执行
- Controller传递已解析的指令结构

### D4: 错误处理
**选择**: 遇到无效指令或n<=0时返回，不执行
**理由**:
- 兼容性：不破坏现有测试
- 防御性：忽略无效输入

## Risks / Trade-offs

- **风险**: 嵌套层数过多导致栈溢出
  - **缓解**: 限制递归深度（或在实际使用中观察Stack使用情况）

- **风险**: n为负数或0的处理方式不明确
  - **缓解**: 返回（无操作），不报错