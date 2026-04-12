## 背景

当前RobotExecutor项目中，DangerZoneObserver和CleanZoneObserver各自独立管理坐标点资源：
- DangerZoneObserver只支持设置单个告警点
- CleanZoneObserver只支持设置单个清扫点
- 两者各自维护独立状态，无法共享资源
- 缺少取消已配置坐标点的接口
- 缺少清扫后自动回收槽位的机制

需求要求：Config组件可以反复调用接口配置/取消Executor组件的告警坐标点和清扫坐标点，配置的坐标点不重复，Executor最多只能存在16个已配置的待告警或待清扫点（共享），清扫后自动回收槽位。

## 目标 / 非目标

**目标：**
- 实现统一的ZoneManager类管理16个共享槽位
- 支持添加（AddPoint）和取消（RemovePoint）坐标点
- 告警点和清扫点共享16个槽位资源
- 清扫后自动回收槽位资源
- 保持现有Observer接口兼容

**非目标：**
- 不修改现有的PositionObserver接口签名
- 不修改RobotExecutor的核心移动逻辑
- 不支持持久化存储坐标点

## 设计决策

### 1. 使用组合模式而非继承

**决策**：ZoneManager作为独立类，不继承PositionObserver，而是持有一组PositionObserver指针。

**理由**： 
- 保持单一职责，ZoneManager专注资源管理
- 避免继承层次过深
- 更好的可测试性

**备选方案**：让ZoneManager继承PositionObserver → 否定原因：职责过杂

### 2. 使用数组存储槽位

**决策**：使用std::array<ZoneSlot, 16>存储槽位，而非std::vector或std::map。

**理由**：
- 固定大小16个槽位，数组足够且效率高
- 避免动态内存分配开销
- 简单直观，索引即槽位号

**备选方案**：std::map<坐标, ZoneSlot> → 否定原因：增加复杂度，坐标本身已是键

### 3. 保持Observer接口兼容

**决策**：DangerZoneObserver和CleanZoneObserver通过委托方式调用ZoneManager，保留原有接口。

**理由**：
- 现有代码无需修改
- 渐进式迁移，降低风险
- 符合开闭原则

## 风险与权衡

- **风险**：线程安全问题 → 当前设计为单线程，同一RobotExecutor实例不会并发访问ZoneManager
- **风险**：坐标点重复判断 → AddPoint时检查坐标是否存在，避免重复添加
- **权衡**：空间换时间 → 使用固定数组而非动态结构，查询时需要遍历

## 迁移计划

1. 新增ZoneManager类（头文件和实现文件）
2. 修改RobotExecutor添加ZoneManager指针成员
3. 更新DangerZoneObserver和CleanZoneObserver使用ZoneManager
4. 添加单元测试验证功能
5. 集成测试验证端到端流程

## 开放问题

- 是否需要支持查询所有已配置坐标点的接口？
- 是否需要支持批量添加/删除坐标点？