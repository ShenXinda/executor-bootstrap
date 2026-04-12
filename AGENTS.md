# AGENTS.md

## 技术栈
- 语言：C++，标准 C++11 或 C++14（使用最新语法特性：auto、智能指针、lambda、范围for等）,不要用C++17及以上新语法
- 编译环境：支持C++14的编译器（GCC 5+ / Clang 3.4+ / MSVC 2015+）

## 代码设计约束
- 优先考虑合适的设计模式（如策略模式、命令模式、观察者模式等），需明确说明使用了哪种模式及其理由
- 遵循SOLID原则，保持接口简洁、职责单一
- 优先使用RAII，避免裸指针和手动new/delete
- 使用constexpr、override、final等现代C++关键字

## 测试要求
- 提供单元测试用例（推荐Google Test框架）
- 测试应覆盖正常流程、边界条件和默认行为

## 协作规范
- 遇到需求理解不明确、歧义或缺失信息时，**必须先提问澄清**，不要猜测或假设
- 提供代码后附带简要的设计说明和编译运行方式，按md格式存放于doc目录下，其中设计图使用paltuml实现

## 输出格式
- 头文件(.h)和实现文件(.cpp)分开
- 使用include guard
- 函数的花括号使用Allman 风格，参考：
void foo()
{
    // do something
}
- if、for、while、switch等控制语句的花括号使用K&R风格，不允许存在不使用花括号的单行，参考：
if () {
    // do something
}

## 代码规范
- 变量名使用小驼峰，类成员变量以下划线结尾
- 函数名、类名使用大驼峰
- 单个函数尽量不要超过50行
- 使用跨平台一致的整数类型，如int32_t、size_t、ssize_t等
- 常量名使用k + CamelCase风格

## Build Commands

All development requires Docker. The project uses `ccup.sh` as the task runner:

| Flag | Action |
|------|--------|
| `-e` | Launch Docker environment (required first) |
| `-u` | Update dependencies & generate CMake files |
| `-b` | Build project |
| `-t` | Run tests (finds `*_test` executables in build/) |
| `-r` | Run the built executable |
| `-i` | Install |
| `-c` | Clean build artifacts |
| `-C` | Clean everything (build + deps) |

Common combinations: `./ccup.sh -ubt` (update + build + test), `./ccup.sh -bi` (build + install).

## Project Structure

- **src/** - C/C++ source files + CMakeLists.txt
- **include/** - Public headers
- **test/** - Test files (CMakeLists.txt with ENABLE_TEST=on)
- **build/** - CMake output (gitignored)
- **deps/** - CPM cached dependencies (gitignored)

## CMake Notes

- Requires out-of-source builds (cannot run in project root)
- Uses CPM.cmake for dependency management
- Tests disabled by default; enable with `-DENABLE_TEST=on`
- Test executables are named `*_test` pattern

## OpenCode Workflow

The `.opencode/` directory contains experimental workflow skills (opsx-propose, opsx-apply, opsx-explore, opsx-archive). These manage changes in `openspec/` directory.

## Notes

- Docker image: `magicbowen/ubuntu-cc-dev:v2`
- Git SSL verification disabled for CMake fetches
- Windows users: uses `winpty docker` and MinGW Makefiles