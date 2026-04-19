## ADDED Requirements

### Requirement: TurnRound动作
Executor组件 SHALL 提供turnRound接口，执行旋转180度动作（右转两次），位置不变。

#### Scenario: 朝向北时执行TurnRound
- **WHEN** 在朝向北时调用turnRound
- **THEN** 朝向变为南，位置不变

#### Scenario: 朝向东时执行TurnRound
- **WHEN** 在朝向东时调用turnRound
- **THEN** 朝向变为西，位置不变

#### Scenario: 朝向南时执行TurnRound
- **WHEN** 在朝向南时调用turnRound
- **THEN** 朝向变为北，位置不变

#### Scenario: 朝向西时执行TurnRound
- **WHEN** 在朝向西时调用turnRound
- **THEN** 朝向变为东，位置不变

#### Scenario: 未初始化时执行TurnRound
- **WHEN** 在未调用Initialize的情况下调用turnRound
- **THEN** 朝向变为南（默认北右转两次），位置不变

### Requirement: 多步前移动作
Executor组件 SHALL 提供forward(int32_t steps)接口，执行沿当前朝向前进n步的动作。

#### Scenario: 多步前进
- **WHEN** 在朝向北且位置为(0, 0)时调用forward(3)
- **THEN** 位置变为(0, 3)，朝向不变

#### Scenario: 多步前进朝向东
- **WHEN** 在朝向东且位置为(0, 0)时调用forward(5)
- **THEN** 位置变为(5, 0)，朝向不变

#### Scenario: 多步前进朝向南
- **WHEN** 在朝向南且位置为(5, 5)时调用forward(2)
- **THEN** 位置变为(5, 3)，朝向不变

#### Scenario: 多步前进朝向西
- **WHEN** 在朝向西且位置为(5, 5)时调用forward(4)
- **THEN** 位置变为(1, 5)，朝向不变

#### Scenario: 步数为0时前进
- **WHEN** 调用forward(0)
- **THEN** 位置不变，无效果

#### Scenario: 负数步数前进
- **WHEN** 调用forward(-1)
- **THEN** 位置不变，无效果

#### Scenario: 未初始化时前进
- **WHEN** 在未调用Initialize的情况下调用forward(3)
- **THEN** 位置变为(0, 3)，朝向变为北

### Requirement: 多步后退动作
Executor组件 SHALL 提供backward(int32_t steps)接口，执行沿当前朝向后退n步的动作。

#### Scenario: 多步后退
- **WHEN** 在朝向北且位置为(0, 3)时调用backward(2)
- **THEN** 位置变为(0, 1)，朝向不变

#### Scenario: 多步后退朝向东
- **WHEN** 在朝向东且位置为(5, 0)时调用backward(3)
- **THEN** 位置变为(2, 0)，朝向不变

#### Scenario: 多步后退朝向南
- **WHEN** 在朝向南且位置为(5, 3)时调用backward(2)
- **THEN** 位置变为(5, 5)，朝向不变

#### Scenario: 多步后退朝向西
- **WHEN** 在朝向西且位置为(3, 5)时调用backward(1)
- **THEN** 位置变为(4, 5)，朝向不变

#### Scenario: 步数为0时后退
- **WHEN** 调用backward(0)
- **THEN** 位置不变，无效果

#### Scenario: 负数步数后退
- **WHEN** 调用backward(-1)
- **THEN** 位置不变，无效果

#### Scenario: 未初始化时后退
- **WHEN** 在未调用Initialize的情况下调用backward(3)
- **THEN** 位置变为(0, -3)，朝向变为北

### Requirement: TurnRound触发告警和清扫
Executor组件 SHALL 在执行TurnRound动作指令时触发告警和清扫活动，仅触发一次。

#### Scenario: TurnRound触发告警和清扫
- **WHEN** 执行turnRound且当前位置存在危险区或清扫区
- **THEN** 触发告警和清扫活动，仅触发一次

#### Scenario: Forward多步移动不额外触发告警
- **WHEN** 执行forward(3)且路径上存在危险区或清扫区
- **THEN** 不触发额外的告警和清扫活动（仅在每步移动时检查）

#### Scenario: Backward多步移动不额外触发告警
- **WHEN** 执行backward(3)且路径上存在危险区或清扫区
- **THEN** 不触发额外的告警和清扫活动（仅在每步移动时检查）