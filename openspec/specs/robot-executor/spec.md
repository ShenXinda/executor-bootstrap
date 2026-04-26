## Purpose

RobotExecutor组件负责控制机器人的移动和位置管理。

## ADDED Requirements

### Requirement: Executor初始化接口
Executor组件 SHALL 提供初始化接口，允许将扫地机初始化在指定位置(x, y, heading)。

#### Scenario: 正常初始化
- **WHEN** 调用Initialize(x, y, heading)接口，其中x和y为整数，heading为有效方向
- **THEN** 扫地机位置设置为(x, y)，朝向设置为heading

#### Scenario: 重复初始化
- **WHEN** 在已经初始化后再次调用Initialize(x, y, heading)
- **THEN** 扫地机位置和朝向被覆盖为新值

### Requirement: 右转动作
Executor组件 SHALL 提供turnRight接口，执行右转90度动作。

#### Scenario: 右转动作执行
- **WHEN** 在朝向北时调用turnRight
- **THEN** 朝向变为东，位置不变

#### Scenario: 连续右转
- **WHEN** 连续调用四次turnRight
- **THEN** 回到原朝向，位置不变

### Requirement: 左转动作
Executor组件 SHALL 提供turnLeft接口，执行左转90度动作。

#### Scenario: 左转动作执行
- **WHEN** 在朝向北时调用turnLeft
- **THEN** 朝向变为西，位置不变

#### Scenario: 连续左转
- **WHEN** 连续调用四次turnLeft
- **THEN** 回到原朝向，位置不变

### Requirement: 状态查询接口
Executor组件 SHALL 提供查询接口，返回当前坐标位置和朝向。

#### Scenario: 查询已初始化的状态
- **WHEN** 在已经初始化后查询状态
- **THEN** 返回当前坐标(x, y)和朝向

#### Scenario: 查询未初始化的状态
- **WHEN** 在未调用Initialize的情况下查询状态
- **THEN** 返回坐标(0, 0)和朝向北

### Requirement: Heading方向枚举
Heading SHALL 包含四个方向：东、南、西、北。

#### Scenario: 四个方向取值
- **WHEN** 查询当前朝向
- **THEN** 返回值属于{北, 东, 南, 西}之一

## MODIFIED Requirements

### Requirement: 前移动作
Executor组件 SHALL 提供forward接口，执行沿当前朝向前进一步的动作。

#### Scenario: 朝向北时前进
- **WHEN** 在朝向为North时调用forward
- **THEN** y坐标增加1，x坐标不变，朝向不变

#### Scenario: 朝向东时前进
- **WHEN** 在朝向为East时调用forward
- **THEN** x坐标增加1，y坐标不变，朝向不变

#### Scenario: 朝向南时前进
- **WHEN** 在朝向为South时调用forward
- **THEN** y坐标减少1，x坐标不变，朝向不变

#### Scenario: 朝向西时前进
- **WHEN** 在朝向为West时调用forward
- **THEN** x坐标减少1，y坐标不变，朝向不变

#### Scenario: 未初始化时前进
- **WHEN** 在未调用Initialize的情况下调用forward
- **THEN** 位置不变，无效果

### Requirement: 后退动作
Executor组件 SHALL 提供backward接口，执行沿当前朝向后退一步的动作。

#### Scenario: 朝向北时后退
- **WHEN** 在朝向为North时调用backward
- **THEN** y坐标减少1，x坐标不变，朝向不变

#### Scenario: 朝向东时后退
- **WHEN** 在朝向为East时调用backward
- **THEN** x坐标减少1，y坐标不变，朝向不变

#### Scenario: 朝向南时后退
- **WHEN** 在朝向为South时调用backward
- **THEN** y坐标增加1，x坐标不变，朝向不变

#### Scenario: 朝向西时后退
- **WHEN** 在朝向为West时调用backward
- **THEN** x坐标增加1，y坐标不变，朝向不变

#### Scenario: 未初始化时后退
- **WHEN** 在未调用Initialize的情况下调用backward
- **THEN** 位置不变，无效果

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

### Requirement: 设置危险点
RobotExecutor组件 SHALL 提供SetDangerPoint接口，允许设置危险点坐标。

#### Scenario: 正常设置危险点
- **WHEN** 调用SetDangerPoint(5, 3)
- **THEN** 返回true，危险点设置为(5, 3)

#### Scenario: 重复设置危险点
- **WHEN** 在已设置危险点后再次调用SetDangerPoint(2, 1)
- **THEN** 返回true，危险点更新为(2, 1)

### Requirement: 清除危险点
RobotExecutor组件 SHALL 提供ClearDangerPoint接口，清除已设置的危险点。

#### Scenario: 清除已设置的危险点
- **WHEN** 在已设置危险点后调用ClearDangerPoint
- **THEN** 返回true，危险点被清除

#### Scenario: 清除未设置的危险点
- **WHEN** 在未设置危险点时调用ClearDangerPoint
- **THEN** 返回true（无操作）

### Requirement: 设置清扫点
RobotExecutor组件 SHALL 提供SetCleanPoint接口，允许设置清扫点坐标。

#### Scenario: 正常设置清扫点
- **WHEN** 调用SetCleanPoint(3, 7)
- **THEN** 返回true，清扫点设置为(3, 7)

#### Scenario: 重复设置清扫点
- **WHEN** 在已设置清扫点后再次调用SetCleanPoint(1, 2)
- **THEN** 返回true，清扫点更新为(1, 2)

### Requirement: 清除清扫点
RobotExecutor组件 SHALL 提供ClearCleanPoint接口，清除已设置的清扫点。

#### Scenario: 清除已设置的清扫点
- **WHEN** 在已设置清扫点后调用ClearCleanPoint
- **THEN** 返回true，清扫点被清除

#### Scenario: 清除未设置的清扫点
- **WHEN** 在未设置清扫点时调用ClearCleanPoint
- **THEN** 返回true（无操作）