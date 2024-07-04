#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t serial_task_handle;

void serial_task(void *data)
{
         printf("AKANKSHA SACHAN\n");
         vTaskDelete(serial_task_handle);
}
void app_main()
{
    printf("RTOS\n");
    printf("DESD\n");
      BaseType_t res = xTaskCreate(serial_task,"SERIAL_TASK",2048,NULL,6,&serial_task_handle);
      if(res==pdPASS)
      {
        printf("task successfully created\n");
      }
}