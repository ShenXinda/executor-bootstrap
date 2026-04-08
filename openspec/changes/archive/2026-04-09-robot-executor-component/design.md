## Context

扫地机器人控制系统需要Executor组件，负责管理机器人位置(x, y)和朝向(heading)，并执行动作指令。当前需求：
- 初始化接口：设置位置(x, y, heading)
- 动作指令：turn right(右转90度)、turn left(左转90度)
- 状态查询：获取当前坐标和朝向
- 默认状态：未初始化时返回(0, 0, 朝向北)

heading取值为四个方向：东、南、西、北（枚举）。

## Goals / Non-Goals

**Goals:**
- 实现Executor组件的初始化接口
- 实现动作指令执行接口(turn right, turn left)
- 实现状态查询接口
- 确保未初始化时有合理的默认值
- 提供完整的单元测试

**Non-Goals:**
- Controller组件的实现（后续任务）
- 路径规划算法
- 地图绘制功能
- 避障功能

## Decisions

### 1. Heading方向枚举设计
采用整数枚举表示四个方向，便于计算和扩展：
- 0: 北
- 1: 东
- 2: 南
- 3: 西

**选择理由**：整数便于取模运算，右转 `(heading + 1) % 4`，左转 `(heading + 3) % 4`。

### 2. 接口设计模式
采用现代C++设计：
- 使用`class`定义`RobotExecutor`类
- 使用`enum class`定义`Heading`枚举
- 使用结构体返回位置信息
- 使用标志位表示未初始化状态

### 3. RAII资源管理
- 使用智能指针管理动态资源
- 避免裸指针和手动内存管理

## Risks / Trade-offs

**风险1**: 坐标超出边界
-  Mitigation: 暂不限制坐标范围，后续可扩展边界检查

**风险2**: 多次初始化覆盖
-  Mitigation: 允许重复初始化，覆盖当前状态
