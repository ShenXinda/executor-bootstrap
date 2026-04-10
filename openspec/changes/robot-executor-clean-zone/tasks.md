## 1. 头文件修改

- [x] 1.1 在robot_executor.h中添加SetCleanPoint方法声明（复用已有SetDangerPoint）
- [x] 1.2 添加清扫坐标成员变量（复用danger point相关机制）

## 2. 观察者模式实现

- [x] 2.1 创建CleanZoneObserver类（clean_zone_observer.h + .cpp）
- [x] 2.2 实现SetCleanPoint方法
- [x] 2.3 实现去重逻辑（hasCleaned_标志）
- [x] 2.4 实现Reset方法用于重置触发状态

## 3. RobotExecutor集成

- [x] 3.1 修改RobotExecutor支持CleanZoneObserver
- [x] 3.2 在Initialize时调用Observer的Reset（如需要）

## 4. 单元测试

- [x] 4.1 添加SetCleanPoint测试用例
- [x] 4.2 添加Forward到达清扫点测试
- [x] 4.3 添加Backward到达清扫点测试
- [x] 4.4 添加重复到达不触发测试
- [x] 4.5 添加重新Initialize后再次触发测试
- [x] 4.6 添加未设置清扫点不触发测试
- [x] 4.7 添加移动到非清扫点不触发测试
- [x] 4.8 编译并运行测试验证