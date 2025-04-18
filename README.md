
# pid

一个灵活且高效的PID控制器库，适用于嵌入式系统、机器人控制、自动化调节和其他需要PID控制算法的场景。该库支持多种PID控制模式（P、PI、PD、PID）和自定义PID量化函数，具有良好的扩展性和易用性。

## 特性

- **多种控制模式**：支持P、PI、PD和PID四种经典控制模式。
- **灵活的量化函数**：提供自定义PID量化函数的接口，适应不同硬件和控制要求。
- **动态参数调节**：可以在运行时动态调整PID的增益系数（Kp、Ki、Kd）和其他控制参数。
- **目标更新与状态重置**：支持实时更新目标值并重置控制器的状态（如误差和积分项）。
- **积分限幅**：防止积分项超出限制，避免积分饱和问题。

## 安装

1. 克隆该仓库：

   ```bash
   git clone https://github.com/Falling-In-Scilence/pid.git
   ```

2. 将`pid.c`和`pid.h`文件集成到你的项目中。

3. 在你的项目中包含`pid.h`头文件，并根据需要使用PID控制器。

## 使用示例

### 初始化PID控制器

```c
#include "pid.h"

// 自定义量化函数
int custom_quantization(float Uk)
{
    // 量化逻辑，可以根据实际需求修改
    return (int)Uk;
}

void main()
{
    PID pid;

    // 初始化PID控制器，设置PID系数和控制时间间隔
    PID_Init(&pid, 1.0f, 0.5f, 0.1f, 0.01f, 100.0f, custom_quantization);

    // 设置目标值
    PID_Set_Target(&pid, 50.0f);

    // 进入控制循环
    while (1)
    {
        // 获取当前系统状态（例如传感器读取值）
        float current_value = get_current_value();

        // 更新PID控制器，计算控制输出
        int control_signal = PID_Update(&pid, current_value);

        // 应用控制信号到系统（例如驱动电机、执行器等）
        apply_control_signal(control_signal);
    }
}
```

### 动态调整PID系数

```c
void adjust_PID_parameters(PID* pid)
{
    // 修改PID系数并调整控制器
    PID_Set_Factor(pid, 1.5f, 0.8f, 0.2f);
}
```

### 更改PID控制模式

```c
void switch_PID_mode(PID* pid)
{
    // 设置不同的控制模式
    PID_Set_Mode(pid, PID_MODE_PI);  // 切换为PI控制模式
}
```

## 函数说明

### `PID_Init`
初始化PID控制器。

```c
void PID_Init(PID* self, float Kp, float Ki, float Kd, float DeltaT, float Target, int (*PID_Control_Quantization_Fucntion)(float Uk));
```
- `Kp`、`Ki`、`Kd`：PID增益系数。
- `DeltaT`：控制周期（时间间隔）。
- `Target`：控制目标。
- `PID_Control_Quantization_Fucntion`：自定义PID量化函数，用于将PID计算结果转化为可用控制信号。

### `PID_Set_Target`
设置目标值并重置PID状态。

```c
void PID_Set_Target(PID* self, float target);
```
- `target`：目标值。

### `PID_Update`
更新PID控制器，计算控制输出。

```c
int PID_Update(PID* self, float current);
```
- `current`：当前系统的实际值。

### `PID_Reset_State`
重置PID控制器的状态（如误差和积分项）。

```c
void PID_Reset_State(PID* self);
```

### `PID_Set_Mode`
设置PID控制模式。

```c
void PID_Set_Mode(PID* self, PID_Mode_Type mode);
```
- `mode`：控制模式，支持`PID_MODE_P`、`PID_MODE_PI`、`PID_MODE_PD`、`PID_MODE_PID`。

### `PID_Set_Factor`
动态调整PID系数。

```c
void PID_Set_Factor(PID* self, float Kp, float Ki, float Kd);
```
- `Kp`、`Ki`、`Kd`：PID增益系数。

## 项目结构

```
pid/
│
├── pid.h       // PID控制器头文件
├── pid.c       // PID控制器实现文件
├── README.md             // 项目说明文档
└── LICENSE               // 开源许可证
```

## 开源协议

本项目采用 **MIT License** 开源协议，具体内容请参见 [LICENSE](LICENSE)。

## 贡献

欢迎提交pull request或issue，报告bug或提出改进建议。请确保在提交代码前已运行过相关测试，且遵循项目的代码风格。

## 联系方式

- 作者：Falling-In-Silence(https://github.com/Falling-In-Silence)
- 邮箱：[1952804220@qq.com]
