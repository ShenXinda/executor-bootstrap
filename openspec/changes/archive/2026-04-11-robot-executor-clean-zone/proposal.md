## Why

需要为RobotExecutor组件添加清扫区域功能：当Config组件设置清扫坐标点后，机器人在首次到达该点时应触发Clean组件的清扫接口。

## What Changes

- 在RobotExecutor中新增SetCleanPoint方法，用于设置清扫坐标点
- 在每次位置变化后检测是否到达清扫坐标点
- 到达清扫坐标时调用clean(x, y)触发清扫
- 同一清扫坐标点在同一次初始化后只触发一次clean（去重）

## Capabilities

### New Capabilities
- `clean-zone-alert`: 清扫区域告警功能 - 设置清扫坐标点，机器人到达时触发clean接口

### Modified Capabilities
- 无

## Impact

- RobotExecutor类新增SetCleanPoint方法和相关成员变量
- 需要复用现有的PositionObserver观察者模式实现
- 依赖clean-intf组件的clean接口