#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"
#define core 1
TaskHandle_t task1,task2,task3;
TimerHandle_t tim;

void callTimer(TimerHandle_t xTimer)
{
    printf("Timer Started\n");
}

void single_task1(void *data)
{
        printf("\n---------IN TASK1--------\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
        vTaskDelete(NULL);
}
void single_task2(void *data)
{
     printf("\n---------IN TASK2--------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); 
        vTaskDelete(NULL);
}

void single_task3(void *data)
{
     printf("\n---------IN TASK3--------\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
        xTimerStart(tim,0);
        vTaskDelete(NULL);
}



void app_main()
{
    printf("inside the app_main\n");
  //  BaseType_t res;
    tim = xTimerCreate("Timer",pdMS_TO_TICKS(10000),pdTRUE,0,callTimer);

    if(xTaskCreatePinnedToCore(single_task1,"TASK1",4096,NULL,5,&task1,core)!=pdPASS){
        printf("task1 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task2,"TASK2",4096,NULL,6,&task2,core)!=pdPASS){
        printf("task2 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task3,"TASK3",4096,NULL,7,&task3,core)!=pdPASS){
        printf("task3 not created\n");
    }
    
    
}