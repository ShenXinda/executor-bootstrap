## Context

在RobotExecutor组件已实现转向功能的基础上，扩展移动功能。需要实现forward（前进）和backward（后退）两个动作指令。

坐标轴定义已确认：
- x轴：向左减小，向右增加（x左为西，x右为东）
- y轴：向上增加，向下减小（y上为北，y下为南）

## Goals / Non-Goals

**Goals:**
- 实现Forward()方法：沿当前朝向移动一步
- 实现Backward()方法：沿当前朝向相反方向移动一步
- 确保未初始化状态下调用移动方法无效果
- 添加对应的单元测试

**Non-Goals:**
- 边界检查（坐标范围限制）
- 避障功能
- 路径规划

## Decisions

### 移动方向计算
根据当前朝向确定移动方向：
- North: y + 1（向北）
- East: x + 1（向东）
- South: y - 1（向南）
- West: x - 1（向西）

Backward是Forward的相反方向。

### 实现策略
- 复用现有RobotExecutor类，添加新方法
- 使用Heading枚举的整数值计算移动偏移量
- 未初始化时不执行移动（位置不变）

## Risks / Trade-offs

**风险**: 未初始化时调用移动方法
-  Mitigation: 检查position_是否有值，无值则直接返回

**风险**: 连续移动后坐标溢出
-  Mitigation: 暂不限制范围，后续可扩展边界检查