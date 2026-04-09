## MODIFIED Requirements

### Requirement: 前移动作
Executor组件 SHALL 提供forward接口，执行沿当前朝向前进一步的动作。

#### Scenario: 朝向北时前进
- **WHEN** 在朝向为North时调用forward
- **THEN** y坐标增加1，x坐标不变，朝向不变

#### Scenario: 朝向东时前进
- **WHEN** 在朝向为East时调用forward
- **THEN** x坐标增加1，y坐标不变，朝向不变

#### Scenario: 朝向南时前进
- **WHEN** 在朝向为South时调用forward
- **THEN** y坐标减少1，x坐标不变，朝向不变

#### Scenario: 朝向西时前进
- **WHEN** 在朝向为West时调用forward
- **THEN** x坐标减少1，y坐标不变，朝向不变

#### Scenario: 未初始化时前进
- **WHEN** 在未调用Initialize的情况下调用forward
- **THEN** 位置不变，无效果

### Requirement: 后退动作
Executor组件 SHALL 提供backward接口，执行沿当前朝向后退一步的动作。

#### Scenario: 朝向北时后退
- **WHEN** 在朝向为North时调用backward
- **THEN** y坐标减少1，x坐标不变，朝向不变

#### Scenario: 朝向东时后退
- **WHEN** 在朝向为East时调用backward
- **THEN** x坐标减少1，y坐标不变，朝向不变

#### Scenario: 朝向南时后退
- **WHEN** 在朝向为South时调用backward
- **THEN** y坐标增加1，x坐标不变，朝向不变

#### Scenario: 朝向西时后退
- **WHEN** 在朝向为West时调用backward
- **THEN** x坐标增加1，y坐标不变，朝向不变

#### Scenario: 未初始化时后退
- **WHEN** 在未调用Initialize的情况下调用backward
- **THEN** 位置不变，无效果