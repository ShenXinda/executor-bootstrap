## ADDED Requirements

### Requirement: 设置危险坐标点
Config组件 SHALL 能够设置危险坐标点(x1, y1)。

#### Scenario: 正常设置危险点
- **WHEN** 调用SetDangerPoint(x, y)设置危险坐标
- **THEN** 危险坐标点被保存，机器人移动到该点时触发告警

### Requirement: 危险坐标告警触发
当机器人移动到危险坐标点时，Executor组件 SHALL 调用Alert组件的alert接口触发告警。

#### Scenario: 前进到达危险点
- **WHEN** 机器人在(0, 0)，危险点为(0, 1)，执行Forward
- **THEN** 机器人移动到(0, 1)，且调用alert(IN_DANGEROUS, 0, 1)

#### Scenario: 后退到达危险点
- **WHEN** 机器人在(0, 0)，危险点为(0, -1)，执行Backward
- **THEN** 机器人移动到(0, -1)，且调用alert(IN_DANGEROUS, 0, -1)

#### Scenario: 重复到达危险点
- **WHEN** 机器人反复移动通过危险点(1, 1)
- **THEN** 每次到达危险点都触发告警

#### Scenario: 未设置危险点不告警
- **WHEN** 未调用SetDangerPoint直接移动
- **THEN** 不触发任何告警

#### Scenario: 移动到非危险点不告警
- **WHEN** 危险点为(1, 1)，机器人移动到(0, 0)
- **THEN** 不触发告警