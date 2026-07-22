/* STUB de ui_statusbar_controller.h SOLO para el simulador de PC.
 * La HMI (ui.c) llama a ui_statusbar_set_enabled(); el resto no se usa en el sim. */
#ifndef SIM_UI_STATUSBAR_CONTROLLER_H
#define SIM_UI_STATUSBAR_CONTROLLER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void ui_statusbar_controller_init(void);
void ui_statusbar_controller_deinit(void);
void ui_statusbar_request_refresh(void);
void ui_statusbar_set_enabled(bool wifi, bool eth, bool bt, bool cloud);

#ifdef __cplusplus
}
#endif

#endif /* SIM_UI_STATUSBAR_CONTROLLER_H */
