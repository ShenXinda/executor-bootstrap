## ADDED Requirements

### Requirement: 顺序执行多个指令
RobotExecutor组件 SHALL 提供executeSequence接口，按顺序执行一组指令。

#### Scenario: 执行前进+右转+前进
- **WHEN** 在朝向北且位置为(0, 0)时调用executeSequence([forward, turnRight, forward])
- **THEN** 位置变为(1, 1)，朝向变为东

#### Scenario: 执行后退+左转+后退
- **WHEN** 在朝向北且位置为(0, 2)时调用executeSequence([backward, turnLeft, backward])
- **THEN** 位置变为(0, 0)，朝向变为西

#### Scenario: 执行空序列
- **WHEN** 调用executeSequence([])
- **THEN** 位置不变，无效果

### Requirement: 执行包含多步移动的序列
RobotExecutor组件 SHALL 在序列中支持多步移动指令（forward(n)、backward(n)）。

#### Scenario: 序列中包含多步移动
- **WHEN** 在朝向北且位置为(0, 0)时调用executeSequence([forward(2), turnRight, forward(1)])
- **THEN** 位置变为(1, 3)，朝向变为东