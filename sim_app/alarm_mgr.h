/* STUB de alarm_mgr.h SOLO para el simulador de PC. */
#ifndef SIM_ALARM_MGR_H
#define SIM_ALARM_MGR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ALARM_STATE_NORMAL = 0,
    ALARM_STATE_WARNING,
    ALARM_STATE_ALERT
} alarm_clinical_state_t;

void alarm_mgr_press_mute(void);
void alarm_mgr_test_buzzer(void);
uint32_t alarm_mgr_get_sensor_faults(void);

#ifdef __cplusplus
}
#endif

#endif /* SIM_ALARM_MGR_H */
