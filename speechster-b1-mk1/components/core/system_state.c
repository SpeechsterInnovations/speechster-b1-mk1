#include "system_state.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "SYS";
static bool states[SYS_MAX_STATES];
static SemaphoreHandle_t lock;

void sys_state_init(void) {
    lock = xSemaphoreCreateMutex();
    for (int i = 0; i < SYS_MAX_STATES; ++i) states[i] = false;
    ESP_LOGI(TAG, "System state initialized");
}

void sys_set_state(sys_state_t id, bool value) {
    if (id >= SYS_MAX_STATES) return;
    xSemaphoreTake(lock, portMAX_DELAY);
    states[id] = value;
    xSemaphoreGive(lock);
    ESP_LOGI(TAG, "State %d -> %s", id, value ? "ON" : "OFF");
}

bool sys_get_state(sys_state_t id) {
    if (id >= SYS_MAX_STATES) return false;
    bool v;
    xSemaphoreTake(lock, portMAX_DELAY);
    v = states[id];
    xSemaphoreGive(lock);
    return v;
}
