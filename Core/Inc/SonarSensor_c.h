#ifndef SONARSENSOR_C_H
#define SONARSENSOR_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* Opaque handle for C code */
typedef void* SonarSensor_c_t;

/* Create/destroy */
SonarSensor_c_t SonarSensor_create(GPIO_TypeDef* trigPort, uint16_t trigPin,
                                   TIM_HandleTypeDef* htim, uint32_t channel);
void SonarSensor_destroy(SonarSensor_c_t h);

/* Lifecycle */
void SonarSensor_init(SonarSensor_c_t h);
void SonarSensor_trigger(SonarSensor_c_t h);
float SonarSensor_getDistanceCm(SonarSensor_c_t h);
int SonarSensor_isBusy(SonarSensor_c_t h);

/* IC callback helpers */
void SonarSensor_internalICCallback(SonarSensor_c_t h, uint32_t capture_value);
void SonarSensor_TIM_IC_Callback_Router(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif

#endif /* SONARSENSOR_C_H */
