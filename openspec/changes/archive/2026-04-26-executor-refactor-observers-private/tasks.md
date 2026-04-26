## 1. 创建private目录并移动头文件

- [x] 1.1 创建include/executor/private/目录
- [x] 1.2 移动position_observer.h到private目录
- [x] 1.3 移动danger_zone_observer.h到private目录
- [x] 1.4 移动clean_zone_observer.h到private目录
- [x] 1.5 移动zone_manager.h到private目录

## 2. 更新RobotExecutor头文件

- [x] 2.1 添加SetDangerPoint(int32_t x, int32_t y)方法声明
- [x] 2.2 添加ClearDangerPoint()方法声明
- [x] 2.3 添加SetCleanPoint(int32_t x, int32_t y)方法声明
- [x] 2.4 添加ClearCleanPoint()方法声明
- [x] 2.5 移除或保留RegisterObserver/UnregisterObserver接口

## 3. 构建和验证

- [x] 3.1 使用./ccup.sh -b 构建项目
- [x] 3.2 使用./ccup.sh -t 运行测试