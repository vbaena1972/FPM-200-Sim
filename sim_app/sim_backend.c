/* Backend simulado para el preview de PC.
 * Provee un AppConfig de ejemplo y stubs de las funciones ESP que la HMI llama. */
#include "storage.h"
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

    strcpy(s_cfg.sensors.pressure_unit, "psi");
    strcpy(s_cfg.sensors.flow_unit,     "lpm");
    strcpy(s_cfg.sensors.gas_type,      "o2");
    strcpy(s_cfg.sensors.color_code,    "nfpa");

    /* Límites en kPa (mundo coherente con pressure_kpa que inyecta el main):
       500 psi = 3447 kPa ; 2000 psi = 13790 kPa */
    s_cfg.sensors.alarm_limits.pressure_min = 3447.0f;
    s_cfg.sensors.alarm_limits.pressure_max = 13790.0f;
    s_cfg.sensors.alarm_limits.flow_delta_threshold = 20.0f;
    s_cfg.sensors.alarm_limits.flow_delta_window_ms = 3000;

    s_cfg.wifi.enabled = true;
    s_cfg.eth.enabled = true;
    s_cfg.bt.enabled = true;
    s_cfg.cloud.enabled = true;

    s_init = true;
}

AppConfig *appcfg_cache_peek(void)
{
    ensure_cfg();
    return &s_cfg;
}

/* ---- stubs sin efecto (la HMI los llama pero en el sim no hacen nada) ---- */
void alarm_mgr_press_mute(void) {}
void ui_statusbar_controller_init(void) {}
void ui_statusbar_controller_deinit(void) {}
void ui_statusbar_request_refresh(void) {}
void ui_statusbar_set_enabled(bool wifi, bool eth, bool bt, bool cloud) { (void)wifi;(void)eth;(void)bt;(void)cloud; }
