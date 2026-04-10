## 1. 头文件修改

- [x] 1.1 在robot_executor.h中添加SetDangerPoint方法声明
- [x] 1.2 添加危险坐标成员变量
- [x] 1.3 添加观察者模式支持（RegisterObserver/UnregisterObserver/NotifyPositionChanged）

## 2. 源文件实现

- [x] 2.1 实现RobotExecutor::SetDangerPoint方法
- [x] 2.2 修改Forward方法，添加危险坐标检测和告警触发
- [x] 2.3 修改Backward方法，添加危险坐标检测和告警触发
- [x] 2.4 修改TurnRight方法，转到危险点时告警
- [x] 2.5 修改TurnLeft方法，转到危险点时告警
- [x] 2.6 移除4处重复的alert调用，改用NotifyPositionChanged()

## 3. 观察者模式实现

- [x] 3.1 创建PositionObserver接口（position_observer.h）
- [x] 3.2 创建DangerZoneObserver类（danger_zone_observer.h + .cpp）

## 4. 单元测试

- [x] 4.1 添加SetDangerPoint测试用例（已在robot_executor_test_1.cpp）
- [x] 4.2 添加Forward到达危险点告警测试
- [x] 4.3 添加Backward到达危险点告警测试
- [x] 4.4 添加TurnRight到达危险点告警测试
- [x] 4.5 添加TurnLeft到达危险点告警测试
- [x] 4.6 添加重复到达危险点告警测试
- [x] 4.7 添加未设置危险点不告警测试
- [x] 4.8 添加移动到非危险点不告警测试
- [x] 4.9 编译并运行测试验证

## 5. Mock/Stub

- [x] 5.1 创建test/mock/目录
- [x] 5.2 使用mockcpp实现alert mock（无需stub）