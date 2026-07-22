/* STUB de storage.h SOLO para el simulador de PC.
 * Reproduce únicamente los campos de AppConfig que usa la nueva HMI.
 * NO es el AppConfig real del firmware. */
#ifndef SIM_STORAGE_H
#define SIM_STORAGE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    struct {
        char info_text[32];
        char client[64];
        char model[16];
        char serial[24];
    } general;

    struct {
        char pressure_unit[8];   /* "psi"|"bar"|"kpa" */
        char flow_unit[8];       /* "lpm"|"sccm"|... */
        char gas_type[16];       /* "o2"|"air_med"|"n2o"|"vac" */
        char color_code[8];
        struct {
            float pressure_min, pressure_max;
            float flow_delta_threshold;
            int   flow_delta_window_ms;
        } alarm_limits;
    } sensors;

    struct { bool enabled; } wifi;
    struct { bool enabled; } eth;
    struct { bool enabled; } bt;
    struct { bool enabled; } cloud;
} AppConfig;

/* Único getter que usa la HMI en el sim. */
AppConfig *appcfg_cache_peek(void);

#ifdef __cplusplus
}
#endif

#endif /* SIM_STORAGE_H */
