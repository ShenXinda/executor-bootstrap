## ADDED Requirements

### Requirement: 重复前移动作
RobotExecutor组件 SHALL 提供repeatForward接口，执行将forward重复执行n次的动作。

#### Scenario: 重复前进3次
- **WHEN** 在朝向北且位置为(0, 0)时调用repeatForward(3)
- **THEN** 位置变为(0, 3)，朝向不变

#### Scenario: 重复前进5次朝向东
- **WHEN** 在朝向东且位置为(0, 0)时调用repeatForward(5)
- **THEN** 位置变为(5, 0)，朝向不变

### Requirement: 重复后退动作
RobotExecutor组件 SHALL 提供repeatBackward接口，执行将backward重复执行n次的动作。

#### Scenario: 重复后退2次
- **WHEN** 在朝向北且位置为(0, 3)时调用repeatBackward(2)
- **THEN** 位置变为(0, 1)，朝向不变

### Requirement: 重复转向动作
RobotExecutor组件 SHALL 提供repeatTurnRight接口，执行将turnRight重复执行n次的动作。

#### Scenario: 重复右转2次
- **WHEN** 在朝向北时调用repeatTurnRight(2)
- **THEN** 朝向变为南，位置不变

### Requirement: 重复次数为0或负数
RobotExecutor组件 SHALL 在重复次数小于等于0时不做任何操作。

#### Scenario: 重复次数为0
- **WHEN** 调用repeatForward(0)
- **THEN** 位置不变，无效果

#### Scenario: 重复次数为负数
- **WHEN** 调用repeatForward(-1)
- **THEN** 位置不变，无效果