## Context

RobotExecutor组件已实现移动功能和危险区域观察者模式。需要增加清扫坐标点功能：当Config组件设置清扫坐标点后，机器人在首次到达该点时应触发Clean组件的清扫接口。

Clean组件接口已存在于deps/clean-intf：
- clean(int x, int y)

## Goals / Non-Goals

**Goals:**
- 实现SetCleanPoint方法，设置清扫坐标点
- 在每次位置变化后检测是否到达清扫坐标点
- 到达清扫坐标时调用clean(x, y)触发清扫
- 同一初始化后同一清扫点只触发一次clean（去重）
- 复用现有的PositionObserver观察者模式

**Non-Goals:**
- 多个清扫坐标点管理（仅支持单一清扫点）
- 清扫坐标点与初始化位置冲突检测（由Config保证）
- 初始化位置改变后重新触发（需要显式re-initialize）

## Design

### Architecture - 复用观察者模式

基于已实现的观察者模式，新增CleanZoneObserver类：

```
┌──────────────────┐         ┌───────────────────────┐
│ RobotExecutor    │────────▶│ PositionObserver      │
│ - position_      │         │ + OnPositionChanged()│
│ - observers_    │         └──────────┬───────────┘  │
└──────────────────┘         ┌──────────┴───────────┐
                    ┌─────────────────┐               
                    │ CleanZoneObserver│               
                    │ + OnChanged()   │               
                    └─────────────────┘               
```

### CleanZoneObserver设计

```cpp
class CleanZoneObserver final : public PositionObserver {
public:
    explicit CleanZoneObserver();
    void SetCleanPoint(int32_t x, int32_t y);
    void Reset();  // 重置已触发状态
    void OnPositionChanged(const Position& newPosition) override;

private:
    bool hasCleanPoint_;
    int32_t cleanPointX_;
    int32_t cleanPointY_;
    bool hasCleaned_;  // 同一初始化后是否已触发过
    Position lastInitPos_;  // 记录初始化位置用于检测重初始化
};
```

### 去重逻辑

1. 每次Initialize时调用CleanZoneObserver::Reset()重置hasCleaned_状态
2. OnPositionChanged中检查：
   - 是否已设置清扫点
   - 是否已触发过（hasCleaned_为false）
   - 当前位置是否等于清扫点
3. 触发clean后设置hasCleaned_ = true

### 与DangerZoneObserver对比

| 特性 | DangerZoneObserver | CleanZoneObserver |
|------|-------------------|-------------------|
| 触发方式 | 每次到达都触发 | 只触发一次 |
| 去重机制 | 无 | hasCleaned_标志 |
| 重置时机 | 无需重置 | 每次Initialize时重置 |

## Decisions

### 使用Observation模式而非直接集成
选择在RobotExecutor外部使用Observer模式检测，理由：
- 与DangerZoneObserver实现一致，保持代码风格统一
- 解耦检测逻辑，便于单独测试
- 可灵活添加其他观察者

### 在RobotExecutor中管理Reset时机
CleanZoneObserver的重置需要在Initialize时触发，因此：
- RobotExecutor维护一个CleanZoneObserver指针
- 或者在调用NotifyPositionChanged时额外调用Reset（不够优雅）

更好的方案：RobotExecutor不直接管理Reset，而是让CleanZoneObserver自己检测初始化位置变化。

## Risks / Trade-offs

**风险**: 重新初始化后无法再次触发���清扫
- 当前设计：需要调用Reset()或重新设置SetCleanPoint
- Mitigation: 使用方（Config）在每次Initialize前调用Reset

**风险**: Initialize时机器人已在清扫点（需求说Config保证不会）
- Mitigation: 不在此组件中检测，由Config组件保证