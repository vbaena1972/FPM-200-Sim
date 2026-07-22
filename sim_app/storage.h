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

typedef enum { APP_BT_SEC_JW = 0, APP_BT_SEC_PASSKEY = 1 } app_bt_sec_mode_t;
typedef enum { MUY_BAJO=0, BAJO, BAJO_MEDIO, MEDIO, MEDIO_ALTO, ALTO, MUY_ALTO, MAXIMO } app_bt_tx_power_t;

typedef struct {
    struct {
        char info_text[32];
        char client[64];
        char model[16];
        char serial[24];
        char lang[3];
        struct { char user[16]; char pass[16]; } admin;
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

    struct {
        bool enabled;
        char ssid[33], password[33];
        char ip_mode[8], ip[16], mask[16], gw[16], dns1[16], dns2[16];
    } wifi;

    struct {
        bool enabled;
        char ip_mode[8], ip[16], mask[16], gw[16], dns1[16], dns2[16];
        char hostname[33];
    } eth;

    struct {
        bool enabled;
        bool advertise;
        app_bt_tx_power_t tx_power;
        struct { char name[24]; char pin[8]; app_bt_sec_mode_t sec_mode; } legacy;
    } bt;

    struct {
        bool enabled;
        char type[8];
        char broker_url[128];
        char topic_base[64];
        char ota_url[128];
        int qos, keepalive;
    } cloud;
} AppConfig;

/* API que usa la HMI en el sim (stubs en sim_backend.c). */
AppConfig *appcfg_cache_peek(void);
int        appcfg_save(const AppConfig *in);   /* stub no-op (devuelve 0) */

#ifdef __cplusplus
}
#endif

#endif /* SIM_STORAGE_H */
