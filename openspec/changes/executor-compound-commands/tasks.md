## 1. 头文件更新

- [x] 1.1 添加RepeatCommand结构体定义到robot_executor.h
- [x] 1.2 添加CommandType枚举定义
- [x] 1.3 添加ExecuteCommand(const RepeatCommand& cmd)方法声明

## 2. 实现文件更新

- [x] 2.1 解析repeat命令：RepeatForward(int32_t times)
- [x] 2.2 解析repeat命令：RepeatBackward(int32_t times)
- [x] 2.3 解析repeat命令：RepeatTurnRight(int32_t times)
- [x] 2.4 解析repeat命令：RepeatTurnLeft(int32_t times)
- [x] 2.5 实现命令序列：ExecuteSequence(const std::vector<RepeatCommand>& commands)
- [x] 2.6 处理n<=0的情况（返回，不执行）

## 3. 测试

- [x] 3.1 添加repeat forward测试（重复3次、5次）
- [x] 3.2 添加repeat backward测试
- [x] 3.3 添加repeat turnRight测试
- [x] 3.4 添加命令序列测试（forward+right+forward）
- [x] 3.5 添加嵌套测试（repeat中嵌套序列）

## 4. 构建与验证

- [x] 4.1 使用./ccup.sh -b 构建项目
- [x] 4.2 使用./ccup.sh -t 运行测试