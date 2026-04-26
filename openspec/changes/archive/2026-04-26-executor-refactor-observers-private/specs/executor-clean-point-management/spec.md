## ADDED Requirements

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