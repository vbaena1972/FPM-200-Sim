/* Backend simulado para el preview de PC.
 * Provee un AppConfig de ejemplo y stubs de las funciones ESP que la HMI llama. */
#include "storage.h"
#include "metrics_store.h"
#include "alarm_mgr.h"
#include "ui_statusbar_controller.h"
#include <string.h>

static AppConfig s_cfg;
static bool s_init = false;

static void ensure_cfg(void)
{
    if (s_init) return;
    memset(&s_cfg, 0, sizeof(s_cfg));

    strcpy(s_cfg.general.info_text, "Axira Equipos");
    strcpy(s_cfg.general.client,    "Medidor de gases " "\xC2\xB7" " UCI Torre A"); /* · */
    strcpy(s_cfg.general.model,     "MPF-4200");
    strcpy(s_cfg.general.serial,    "AX-4200-01847");
    strcpy(s_cfg.general.hw_version, "1.1");
    strcpy(s_cfg.general.fw_version, "1.8.0");
    strcpy(s_cfg.general.lang,      "es");
    strcpy(s_cfg.general.timezone,  "America/Bogota");
    s_cfg.general.brightness = 80;
    strcpy(s_cfg.general.admin.pass, "1234");
    strcpy(s_cfg.general.admin.user, "admin");

    strcpy(s_cfg.sensors.pressure_unit, "psi");
    strcpy(s_cfg.sensors.flow_unit,     "lpm");
    strcpy(s_cfg.sensors.gas_type,      "o2");
    strcpy(s_cfg.sensors.color_code,    "nfpa");
    s_cfg.sensors.flow_fullscale_lpm = 100.0f;
    strcpy(s_cfg.sensors.cal.last_cal_date,     "12 mar 2026");
    strcpy(s_cfg.sensors.cal.next_service_date, "08 sep 2026");

    /* Límites en kPa (mundo coherente con pressure_kpa que inyecta el main):
       500 psi = 3447 kPa ; 2000 psi = 13790 kPa */
    s_cfg.sensors.alarm_limits.pressure_min = 3447.0f;
    s_cfg.sensors.alarm_limits.pressure_max = 13790.0f;
    s_cfg.sensors.alarm_limits.flow_delta_threshold = 20.0f;
    s_cfg.sensors.alarm_limits.flow_delta_window_ms = 3000;

    s_cfg.wifi.enabled = true;
    strcpy(s_cfg.wifi.ssid, "Hospital-BIOMED-5G");
    strcpy(s_cfg.wifi.password, "biomed2026");
    strcpy(s_cfg.wifi.ip_mode, "dhcp");
    strcpy(s_cfg.wifi.ip, "10.4.12.87");
    strcpy(s_cfg.wifi.mask, "255.255.255.0");
    strcpy(s_cfg.wifi.gw, "10.4.12.1");
    strcpy(s_cfg.wifi.dns1, "10.4.12.1");

    s_cfg.eth.enabled = false;
    strcpy(s_cfg.eth.hostname, "AX-0001-Eth");
    strcpy(s_cfg.eth.ip_mode, "dhcp");

    s_cfg.bt.enabled = true;
    s_cfg.bt.advertise = true;
    s_cfg.bt.tx_power = ALTO;
    s_cfg.bt.mesh.enabled = false;
    s_cfg.bt.mesh.provisioned = false;
    s_cfg.bt.mesh.ttl = 5;
    s_cfg.bt.mesh.relay = false;
    strcpy(s_cfg.bt.mesh.net_key, "00112233445566778899AABBCCDDEEFF");
    strcpy(s_cfg.bt.mesh.app_key, "FFEEDDCCBBAA99887766554433221100");
    strcpy(s_cfg.bt.mesh.dev_uuid, "123e4567-e89b-12d3-a456-426614174000");
    s_cfg.bt.mesh.unicast_addr = 0x0002;
    strcpy(s_cfg.bt.legacy.name, "MPF-4200-1847");
    strcpy(s_cfg.bt.legacy.pin, "0000");
    s_cfg.bt.legacy.sec_mode = APP_BT_SEC_PASSKEY;

    s_cfg.cloud.enabled = true;
    strcpy(s_cfg.cloud.type, "mqtt");
    strcpy(s_cfg.cloud.broker_url, "broker.axira.io:8883");
    strcpy(s_cfg.cloud.topic_base, "axira");
    s_cfg.cloud.qos = 1;
    s_cfg.cloud.keepalive = 60;

    s_init = true;
}

AppConfig *appcfg_cache_peek(void)
{
    ensure_cfg();
    return &s_cfg;
}

/* En el sim no hay NVS: el AppConfig vive en RAM y ya quedó modificado vía peek. */
int appcfg_save(const AppConfig *in) { (void)in; return 0; }

/* metrics_store stub: 184 días de servicio de demo */
uint32_t appmetrics_service_min(void) { return 184u * 1440u; }

/* ---- stubs sin efecto (la HMI los llama pero en el sim no hacen nada) ---- */
void alarm_mgr_press_mute(void) {}
void ui_statusbar_controller_init(void) {}
void ui_statusbar_controller_deinit(void) {}
void ui_statusbar_request_refresh(void) {}
void ui_statusbar_set_enabled(bool wifi, bool eth, bool bt, bool cloud) { (void)wifi;(void)eth;(void)bt;(void)cloud; }
