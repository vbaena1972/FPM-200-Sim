/* STUB de metrics_store.h SOLO para el simulador de PC.
 * La UI solo usa appmetrics_service_min(); el resto vive en main.c (no compilado en el sim). */
#ifndef SIM_METRICS_STORE_H
#define SIM_METRICS_STORE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t appmetrics_service_min(void);   /* demo: 184 días */

#ifdef __cplusplus
}
#endif

#endif /* SIM_METRICS_STORE_H */
