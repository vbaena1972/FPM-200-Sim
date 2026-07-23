/* STUB de storage.h SOLO para el simulador de PC.
 * Reproduce ÃƒÆ’Ã‚Âºnicamente los campos de AppConfig que usa la nueva HMI.
 * NO es el AppConfig real del firmware. */
#ifndef SIM_STORAGE_H
#define SIM_STORAGE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define APP_MAX_USERS 8
typedef enum { APP_ROLE_NONE=0, APP_ROLE_TECH=1, APP_ROLE_ADMIN=2, APP_ROLE_FACTORY=3 } app_user_role_t;
typedef struct { char name[24]; char pin[24]; app_user_role_t role; bool locked; bool must_change_pin; char last[24]; } app_user_t;
typedef enum { APP_BT_SEC_JW = 0, APP_BT_SEC_PASSKEY = 1 } app_bt_sec_mode_t;
typedef enum { MUY_BAJO=0, BAJO, BAJO_MEDIO, MEDIO, MEDIO_ALTO, ALTO, MUY_ALTO, MAXIMO } app_bt_tx_power_t;

typedef struct {
    struct {
        char info_text[32];
        char client[64];
        char model[16];
        char serial[24];
        char hw_version[16];
        char fw_version[16];
        char lang[3];
        char timezone[32];   /* IANA, p.ej. "America/Bogota" */
        int brightness;      /* 10..100 (%) */
        char theme[8];
        int dim_minutes;
        struct { bool tone_warn; bool tone_alert; int warn_timeout_s; int alert_timeout_s; int volume; int reannounce_minutes; int max_silence_minutes; } alarm;
        int users_count;
        app_user_t users[APP_MAX_USERS];
        app_user_t factory;
        struct { char user[16]; char pass[16]; } admin;
    } general;

    struct {
        char pressure_unit[8];   /* "psi"|"bar"|"kpa" */
        char flow_unit[8];       /* "lpm"|"sccm"|... */
        char gas_type[16];       /* "o2"|"air_med"|"n2o"|"vac" */
        char color_code[8];
        float flow_fullscale_lpm;
        struct {
            char last_cal_date[16];
            char next_service_date[16];
        } cal;
        struct {
            bool pressure_min_enabled, pressure_max_enabled;
            bool flow_delta_enabled, flow_high_enabled;
            float pressure_min, pressure_max;
            float flow_delta_threshold;
            float flow_high_limit;
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
        struct {
            bool enabled;
            bool provisioned;
            uint8_t ttl;
            bool relay;
            char net_key[64];
            char app_key[64];
            char dev_uuid[40];
            uint16_t unicast_addr;
        } mesh;
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
