#pragma once
#include <stdbool.h>

typedef enum {
    SYS_WIFI_READY = 0,
    SYS_AUDIO_ACTIVE,
    SYS_BLE_CONNECTED,
    SYS_THERMAL_SAFE,
    SYS_MAX_STATES
} sys_state_t;

void sys_state_init(void);
void sys_set_state(sys_state_t id, bool value);
bool sys_get_state(sys_state_t id);
