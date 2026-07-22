/* STUB de sensors_runtime.h SOLO para el simulador de PC. */
#ifndef SIM_SENSORS_RUNTIME_H
#define SIM_SENSORS_RUNTIME_H

#include <stdint.h>
#include "storage.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int64_t ts_ms;
    float   pressure_kpa;
    float   flow_lpm;
} sensor_sample_t;

#ifdef __cplusplus
}
#endif

#endif /* SIM_SENSORS_RUNTIME_H */
