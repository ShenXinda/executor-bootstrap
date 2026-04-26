## Context

当前RobotExecutor的头文件中包含了PositionObserver及其子类的头文件，并且暴露了RegisterObserver/UnregisterObserver接口。这违反了封装原则，将内部实现细节暴露给外部。

现有结构：
- include/executor/robot_executor.h - 主头文件，包含position_observer.h
- include/executor/position_observer.h - 位置观察者抽象类
- include/executor/danger_zone_observer.h - 危险区观察者
- include/executor/clean_zone_observer.h - 清扫区观察者
- include/executor/zone_manager.h - 区域管理器

## Goals / Non-Goals

**Goals:**
- 将实现类头文件移入private目录
- RobotExecutor提供危险点/清扫点管理接口
- 隐藏所有内部实现细节

**Non-Goals:**
- 不修改已有的功能逻辑（方法已在RobotExecutor中实现）
- 不移除RegisterObserver接口（保持兼容性）

## Decisions

### D1: private目录位置
**选择**: include/executor/private/
**理由**: 与robot_executor.h在同一目录下，便于包含

### D2: 头文件组织方式
**选择**: 将4个头文件移动到private目录，保持原有类的接口不变
**理由**: 实现类对外部不可见，但需要被robot_executor.cpp包含

### D3: RobotExecutor新增接口
**选择**: 利用已有的impl_->SetDangerPoint()等方法封装新接口
**理由**: 方法已在Impl类中实现，只需暴露RobotExecutor的public接口

## Risks / Trade-offs

- **风险**: 外部代码直接include implementation头文件
  - **缓解**: 将头文件移到private后，外部无法访问
- **风险**: 需要修改CMake或build配置
  - **缓解**: private目录仍在include/executor下，应无需修改