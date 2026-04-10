## ADDED Requirements

### Requirement: 设置清扫坐标点
Config组件能够设置清扫坐标点(x1, y1)。Config组件保证清扫点不会是机器人的初始化位置坐标点和危险点。

#### Scenario: 正常设置清扫点
- **WHEN** 调用SetCleanPoint(x, y)设置清扫坐标
- **THEN** 清扫坐标点被保存，机器人移动到该点时触发清扫

### Requirement: 到达清扫坐标触发清扫
当机器人首次移动到清扫坐标点时，Executor组件 SHALL 调用Clean组件的clean接口触发清扫。

#### Scenario: 前进到达清扫点
- **WHEN** 机器人在(0, 0)，清扫点为(0, 1)，执行Forward
- **THEN** 机器人移动到(0, 1)，且调用clean(0, 1)

#### Scenario: 后退到达清扫点
- **WHEN** 机器人在(0, 0)，清扫点为(0, -1)，执行Backward
- **THEN** 机器人移动到(0, -1)，且调用clean(0, -1)

#### Scenario: 同一初始化后重复到达不触发清扫
- **WHEN** 机器人初始化后已触发过一次clean(x, y)，再次经过该点
- **THEN** 不再次调用clean接口

#### Scenario: 重新初始化后再次触发清扫
- **WHEN** 机器人初始化后已触发过clean，再次Initialize到不同位置后回到原清扫点
- **THEN** 再次调用clean接口

#### Scenario: 未设置清扫点不触发清扫
- **WHEN** 未调用SetCleanPoint直接移动
- **THEN** 不触发任何清扫

#### Scenario: 移动到非清扫点不触发清扫
- **WHEN** 清扫点为(1, 1)，机器人移动到(0, 0)
- **THEN** 不触发清扫