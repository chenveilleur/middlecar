#include "MotorDriver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"  // 或者直接定义

typedef struct {
    float front;
    float left;
    float right;
} SensorData;
// 外部引入传感器数据
extern SensorData g_SensorData;
extern MotorDriver motor;

// --- 算法核心参数设定 (需要你根据实际场地微调) ---
const float WALL_THRESH = 15.0f;    // 判定为"有墙"的阈值 (15厘米)
const float TARGET_DIST_R = 8.0f;   // 我们期望小车贴着右墙走的安全距离 (8厘米)
const float Kp = 3.5f;              // P控制器的比例系数 (差一点距离，补多少速度)
const int BASE_SPEED = 60;          // 直行基础速度 (0-100)，干电池建议别开太快

// --- 盲转辅助函数声明 ---
void TurnRight90();
void TurnLeft90();
void TurnAround180();

void Task_Ctrl(void *argument) {
    // 刚开机，等传感器测几次数据稳定一下
    vTaskDelay(pdMS_TO_TICKS(500)); 

    for(;;) {
        // 读取最新距离
        float dist_F = g_SensorData.front;
        float dist_L = g_SensorData.left;
        float dist_R = g_SensorData.right;

        // 极限保护：如果任何一个超声波测到距离小于 3cm，立刻刹车防撞死
        if (dist_F < 3.0f || dist_L < 3.0f || dist_R < 3.0f) {
            motor.SetTargetSpeed(0, 0);
            vTaskDelay(pdMS_TO_TICKS(100)); // 刹车缓一缓
            continue;
        }

        // ==========================================
        // 核心状态机：右手定则 (优先级：右 -> 前 -> 左 -> 后)
        // ==========================================

        if (dist_R > WALL_THRESH) {
            // 1. 右侧有路：必须右转！
            TurnRight90();
        } 
        else if (dist_F > WALL_THRESH) {
            // 2. 右侧有墙，前方有路：沿墙直行 (启动 P 控制微调)
            
            // 计算右墙距离偏差：正数说明离墙太近了，负数说明离墙太远了
            float error = TARGET_DIST_R - dist_R; 
            
            // 计算速度补偿值
            int adjust = (int)(error * Kp); 

            // 离墙太近 (error>0) -> adjust>0 -> 左轮减速，右轮加速 -> 车头向左偏，远离墙壁
            // 离墙太远 (error<0) -> adjust<0 -> 左轮加速，右轮减速 -> 车头向右偏，靠近墙壁
            int left_speed = BASE_SPEED - adjust;
            int right_speed = BASE_SPEED + adjust;

            motor.SetTargetSpeed(left_speed, right_speed);
        } 
        else if (dist_L > WALL_THRESH) {
            // 3. 右侧和前方都是死路，左侧有路：左转
            TurnLeft90();
        } 
        else {
            // 4. 三面都是墙 (死胡同)：原地掉头
            TurnAround180();
        }

        // 决策频率：20ms 思考一次
        vTaskDelay(pdMS_TO_TICKS(20)); 
    }
}

// --- 盲转动作实现 ---

void TurnRight90() {
    // 步骤 1: 稍微往前开一点点，让车轮轴心越过墙角，防止后轮卡住墙角
    motor.SetTargetSpeed(BASE_SPEED, BASE_SPEED);
    vTaskDelay(pdMS_TO_TICKS(250)); // 往前冲 250ms

    // 步骤 2: 原地右转 (左轮正转，右轮反转)
    motor.SetTargetSpeed(BASE_SPEED, -BASE_SPEED);
    
    // 【终极调参点】：这个延时决定了转弯的角度！
    // 电池电压高的时候可能 400ms 就转了 90度；电压低可能需要 600ms。
    // 需要你在平地上反复测这个值。
    vTaskDelay(pdMS_TO_TICKS(450)); 

    // 步骤 3: 刹车，稳定车身，防止惯性漂移
    motor.SetTargetSpeed(0, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void TurnLeft90() {
    // 左转类似，注意方向相反
    motor.SetTargetSpeed(BASE_SPEED, BASE_SPEED);
    vTaskDelay(pdMS_TO_TICKS(250));

    motor.SetTargetSpeed(-BASE_SPEED, BASE_SPEED);
    vTaskDelay(pdMS_TO_TICKS(450)); // 同样需要下地微调

    motor.SetTargetSpeed(0, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void TurnAround180() {
    // 原地掉头，就是转两次 90 度的时间
    motor.SetTargetSpeed(BASE_SPEED, -BASE_SPEED);
    vTaskDelay(pdMS_TO_TICKS(900)); // 转 180 度的延时

    motor.SetTargetSpeed(0, 0);
    vTaskDelay(pdMS_TO_TICKS(200));
}
