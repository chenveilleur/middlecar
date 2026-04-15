#ifndef MOTORDRIVER_C_H
#define MOTORDRIVER_C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* Opaque handle for C code */
typedef void* MotorDriver_c_t;

MotorDriver_c_t MotorDriver_create(void);
void MotorDriver_destroy(MotorDriver_c_t h);

void MotorDriver_init(MotorDriver_c_t h);
void MotorDriver_setTargetSpeed(MotorDriver_c_t h, int16_t left, int16_t right);
void MotorDriver_update(MotorDriver_c_t h);

#ifdef __cplusplus
}
#endif

#endif /* MOTORDRIVER_C_H */
