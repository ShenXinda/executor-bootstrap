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
