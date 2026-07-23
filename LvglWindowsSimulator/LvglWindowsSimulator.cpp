#include <Windows.h>

#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include <string.h>

/* HMI Axira / Claude Design (fuentes reales de ClaudeHMI-FW/main/ui vía include dir) */
#include "ui.h"
#include "sensors_runtime.h"
#include "storage.h"
#include "alarm_mgr.h"

/* -------- Escenarios de demo (ciclan para ver los 4 estados) --------
 * Presión en kPa (mundo coherente con los límites del sim_backend):
 *   1400 psi ~ 9653 kPa ; 420 psi ~ 2896 kPa ; límite min 500 psi = 3447 kPa
 * Flujo en L/min (unidad "lpm", eje 0..100). */
typedef struct {
    const char *label;
    float pressure_kpa;
    float flow_lpm;
    alarm_clinical_state_t state;
    bool muted;
} scenario_t;

static const scenario_t s_scen[] = {
    { "NORMAL",                965.3f, 59.0f, ALARM_STATE_NORMAL,  false },
    { "ADVERTENCIA (flujo)",   951.5f, 86.0f, ALARM_STATE_WARNING, false },
    { "ALARMA (presion baja)", 289.6f, 44.0f, ALARM_STATE_ALERT, false },
    { "ALARMA SILENCIADA",     289.6f, 44.0f, ALARM_STATE_ALERT,   true  },
};
static int s_idx = 0;

static void apply_scenario(int i)
{
    const scenario_t *s = &s_scen[i];
    int64_t now_ms = (int64_t)lv_tick_get();   /* ts real: el consumo integra el dt */
    sensor_sample_t last = { now_ms, s->pressure_kpa, s->flow_lpm };
    sensor_sample_t mn   = { now_ms, s->pressure_kpa * 0.92f, s->flow_lpm * 0.85f };
    sensor_sample_t mx   = { now_ms, s->pressure_kpa * 1.05f, s->flow_lpm * 1.12f };
    ui_main_update(&last, true, &mn, &mx, true, appcfg_cache_peek(), s->state, s->muted);
    ui_main_set_clock("14:32");
    ui_main_set_date("22/07/2026");
}

static void scenario_timer_cb(lv_timer_t *t)
{
    (void)t;
    s_idx = (s_idx + 1) % (int)(sizeof(s_scen) / sizeof(s_scen[0]));
    apply_scenario(s_idx);
}

int main()
{
    lv_init();

#if LV_TXT_ENC == LV_TXT_ENC_UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    /* Pantalla del dispositivo: ST7796 480x320. Zoom 200% para verla comoda. */
    int32_t zoom_level = 200;
    bool allow_dpi_override = false;
    bool simulator_mode = true;
    lv_display_t* display = lv_windows_create_display(
        L"ClaudeHMI - Axira (480x320)",
        480,
        320,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display)
    {
        return -1;
    }

    HWND window_handle = lv_windows_get_display_window_handle(display);
    if (!window_handle)
    {
        return -1;
    }

    HICON icon_handle = LoadIconW(
        GetModuleHandleW(NULL),
        MAKEINTRESOURCE(IDI_LVGL_WINDOWS));
    if (icon_handle)
    {
        SendMessageW(window_handle, WM_SETICON, TRUE,  (LPARAM)icon_handle);
        SendMessageW(window_handle, WM_SETICON, FALSE, (LPARAM)icon_handle);
    }

    lv_indev_t* pointer_indev = lv_windows_acquire_pointer_indev(display);
    if (!pointer_indev)
    {
        return -1;
    }

    /* Construir la HMI y pintar el primer escenario */
    ui_init();
    apply_scenario(0);

    /* Cicla NORMAL -> ADVERTENCIA -> ALARMA -> SILENCIADA cada 2.5 s */
    lv_timer_create(scenario_timer_cb, 2500, NULL);

    /* Workaround del buffer diferido del driver de Windows (ver sim original):
       bombear timers hasta que exista el draw buffer y forzar un refresco sincrono. */
    for (int guard = 0; guard < 2000 && !lv_display_get_buf_active(display); ++guard) {
        lv_timer_handler();
        lv_delay_ms(1);
    }
    lv_refr_now(display);

    /* El driver de Windows auto-pausa el timer de refresco si el draw buffer aún no
       existía en el primer ciclo. Como esta HMI es DINÁMICA (splash->main, ciclado
       de estados, navegación, timers), hay que reanudarlo para que se siga
       redibujando; si no, la pantalla se congela en el primer frame. */
    lv_timer_t *refr = lv_display_get_refr_timer(display);
    if (refr) lv_timer_resume(refr);

    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
    }

    return 0;
}
