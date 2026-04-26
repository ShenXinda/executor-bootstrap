## ADDED Requirements

### Requirement: repeat嵌套command列表
RobotExecutor组件 SHALL 支持repeat命令嵌套命令列表。

#### Scenario: repeat中嵌套序列
- **WHEN** 在朝向北且位置为(0, 0)时执行repeat([forward, forward], 2)
- **THEN** 位置变为(0, 4)，朝向不变

### Requirement: command列表嵌套repeat
RobotExecutor组件 SHALL 支持命令列表中嵌套repeat命令。

#### Scenario: 序列中嵌套repeat
- **WHEN** 在朝向北且位置为(0, 0)时执行executeSequence([repeat([forward], 2), turnRight])
- **THEN** 位置变为(1, 2)，朝向变为东

### Requirement: 多层嵌套
RobotExecutor组件 SHALL 支持多层嵌套结构。

#### Scenario: 两层嵌套
- **WHEN** 在朝向北且位置为(0, 0)时执行executeSequence([repeat([forward, turnRight], 2), forward])
- **THEN** 位置变为(2, 0)，朝向变为东

### Requirement: 嵌套中的重复次数为0
RobotExecutor组件 SHALL 在嵌套中的重复次数为0时跳过执行。

#### Scenario: 嵌套中repeat次数为0
- **WHEN** 执行repeat([forward], 0)
- **THEN** 位置不变，无效果