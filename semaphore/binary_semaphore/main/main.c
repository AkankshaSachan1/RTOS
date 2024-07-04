#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#define TASKCORE 1
TaskHandle_t task1,task2;
SemaphoreHandle_t mysema;


void serial_task1(void *data)
{
    while(1){
     printf("Inside task1\n");
     vTaskDelay(pdMS_TO_TICKS(1000));
     xSemaphoreGive(mysema);
     printf("signal sent\n");
    }
     vTaskDelete(NULL);      
}

void serial_task2(void *data)
{
    while(1){
       printf("Inside task2\n");
       xSemaphoreTake(mysema,portMAX_DELAY);
       vTaskDelay(pdMS_TO_TICKS(5000));
       printf("signal received\n");
    }
        vTaskDelete(NULL);      
}

void app_main()
{
    BaseType_t res1,res2;
    mysema=xSemaphoreCreateBinary();

    printf("Inside app_main\n");
    res1 = xTaskCreatePinnedToCore(serial_task1,"Task_1",4096,NULL,4,&task1,TASKCORE);
    if(res1!=pdPASS)
    {
        printf("task 1 not created\n");
    }
     res2 = xTaskCreatePinnedToCore(serial_task2,"Task_2",4096,NULL,8,&task2,TASKCORE);
    if(res2!=pdPASS)
    {
        printf("task 2 not created\n");
    }
     
}
