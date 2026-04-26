## ADDED Requirements

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