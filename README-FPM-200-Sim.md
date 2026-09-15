# Simulador de PC — HMI Axira / Claude Design

Copia independiente del simulador LVGL para Windows/Visual Studio, cableada para renderizar la **nueva
HMI** de `FPM-200` en un preview de 480×320 (misma resolución que el ST7796 del dispositivo).

- No toca tu simulador original (`lv_port_pc_visual_studio`) ni su otro proyecto.
- Compila **las fuentes reales** de `..\FPM-200\main\ui` (no copias), así que lo que ves aquí es lo
  mismo que se compila para la placa. Editas una vez y ambos lo ven.
- Las dependencias del firmware (sensores, alarmas, config, red) se sustituyen por **stubs** en `sim_app\`.

## Cómo compilar y correr

1. Abre `LVGL.slnx` en Visual Studio (misma versión con la que usas el simulador original).
2. Proyecto de inicio: **LvglWindowsSimulator** (clic derecho → *Set as Startup Project*).
3. Configuración **Debug | x64** → *Ejecutar* (F5) o *Compilar* (Ctrl+B).

Debe abrirse una ventana con la pantalla principal a 480×320 (zoom 200%). Cada 2.5 s cicla los 4 estados:
**NORMAL → ADVERTENCIA → ALARMA → ALARMA SILENCIADA**, para revisar todos los looks.

## Qué toca cada archivo (por si quieres ajustar)

| Archivo | Rol |
|---|---|
| `LvglWindowsSimulator\LvglWindowsSimulator.cpp` | `main`: crea ventana 480×320, llama `ui_init()` y cicla escenarios |
| `sim_app\storage.h` / `sensors_runtime.h` / `alarm_mgr.h` | Stubs de tipos ESP (AppConfig, sensor_sample_t, estados de alarma) |
| `sim_app\sim_backend.c` | Config de ejemplo (`appcfg_cache_peek`) + stubs sin efecto |
| `LvglWindowsSimulator\lv_conf.h` | Config LVGL del sim (32bpp; el device usa 16bpp — solo cambia precisión de color, no el layout) |
| `LvglWindowsSimulator.vcxproj` | Include dirs → `FPM-200\main\ui` + `sim_app`; lista de fuentes de la HMI |

## Notas
- Los valores de presión se inyectan en kPa en un "mundo coherente" con los límites del `sim_backend`
  (500 psi = 3447 kPa, etc.) para que el estado NORMAL/BAJA salga correcto. El flujo va en L/min (eje 0–100).
  Esto es solo para el preview; en la placa vienen de los sensores reales.
- Si Visual Studio se queja de archivos en el *Solution Explorer* que ya no existen (filtros heredados del
  proyecto original), es cosmético: el build usa solo el `.vcxproj`.

## Para iterar el diseño
Manda un screenshot de la ventana y te digo (o ajusto) qué cambiar en las pantallas. Al editar los `.c/.h`
de `FPM-200\main\ui`, recompila el sim para ver el cambio; el mismo código va a la placa.
