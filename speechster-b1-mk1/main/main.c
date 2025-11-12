#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "system_state.h"

void heartbeat_task(void *arg) {
    const char *TAG = "HEART";
    while (1) {
        ESP_LOGI(TAG, "System running... uptime=%lu ms",
                 (unsigned long)(xTaskGetTickCount() * portTICK_PERIOD_MS));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Optional FreeRTOS Idle Hook (required if CONFIG_FREERTOS_USE_IDLE_HOOK=y)
void vApplicationIdleHook(void)
{
    // Do nothing, but must exist
    __asm__ __volatile__("nop");
}

void app_main(void) {
    const char *TAG = "BOOT";
    ESP_LOGI(TAG, "Speechster-B1 MK1 Booting...");
    sys_state_init();

    sys_set_state(SYS_WIFI_READY, false);
    sys_set_state(SYS_AUDIO_ACTIVE, false);

    xTaskCreatePinnedToCore(heartbeat_task, "heartbeat", 2048, NULL, 2, NULL, 0);
}
