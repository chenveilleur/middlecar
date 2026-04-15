#pragma once

// 包含 HAL 库的核心头文件。CubeMX 生成的工程通常只需要包含 main.h
#include "main.h" 
#define ACCEL_STEP 5

class MotorDriver {
private:
    // 当前实际输出给电机的速度 (-100 到 100)
    int16_t currentSpeedL;
    int16_t currentSpeedR;

    // 目标期望速度 (-100 到 100)
    int16_t targetSpeedL;
    int16_t targetSpeedR;

    // 软启动步进值：每次 Update() 允许的最大速度变化量
    // 值越小，加速越平滑，干电池越安全；但也意味着响应越慢。
    // 假设 Update() 每 10ms 调用一次，步进设为 5，则 0 加速到 100 需要 200ms。

    // 内部硬件操作函数（不对外暴露）
    void SetHardwarePWM_L(int16_t speed);
    void SetHardwarePWM_R(int16_t speed);

public:
    MotorDriver();
    
    // 初始化函数：启动定时器 PWM
    void Init();

    // 设定目标速度（供 Ctrl 任务调用）
    // 输入范围：-100 (全速后退) 到 100 (全速前进)，0 为停止
    void SetTargetSpeed(int16_t speedL, int16_t speedR);

    // 更新函数（必须在 Motor 任务中高频循环调用，例如每 10ms 一次）
    void Update();
};
