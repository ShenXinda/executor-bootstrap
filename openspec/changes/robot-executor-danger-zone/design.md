## Context

RobotExecutor组件已实现移动功能，需要增加危险坐标点告警功能。当Config组件设置危险坐标点后，机器人在移动到该点时应触发Alert组件的告警。

Alert组件接口已存在于deps/alert-intf：
- alert(AlertType type, int x, int y)
- type = IN_DANGEROUS (3) 表示"经过危险坐标告警"

## Goals / Non-Goals

**Goals:**
- 实现SetDangerPoint方法，设置危险坐标点
- 在每次移动后检测是否到达危险坐标点
- 到达危险坐标时调用alert(IN_DANGEROUS, x, y)触发告警
- 支持重复触发告警（同一点多次经过）

**Non-Goals:**
- 多个危险坐标点管理（仅支持单一危险点）
- 危险坐标点与初始化位置冲突检测（由Config保证）
- 告警后的自动规避行为

## Decisions

### 危险点检测时机
选择在移动**后**检测危险坐标，而非移动**前**。这样可以确保告警触发时机器人确实到达了该位置。

### 告警触发策略
- 每次移动到危险坐标时都触发告警（重复触发）
- 在危险坐标点转向也要触发告警
- 使用alert接口，传入当前危险坐标的x, y值

### 数据结构
使用std::optional<Position>表示可选的危险坐标点：
- 未设置时为std::nullopt
- 设置后存储危险点坐标

## Risks / Trade-offs

**风险**: 危险坐标未设置时调用告警
- Mitigation: 仅在已设置危险坐标且移动到达该坐标时才触发告警

**风险**: 初始化位置就是危险点（需求说Config保证不会）
- Mitigation: 不在此组件中检测，由Config组件保证