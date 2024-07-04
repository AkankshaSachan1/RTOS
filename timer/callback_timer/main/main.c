#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#define TASKCORE 1
TaskHandle_t task1,task2,task3;
TimerHandle_t timer1;
void callbacktimer(TimerHandle_t xTimer)
{
    printf("Timer fired\n");
}
void serial_task1(void *parameters)
{
    while(1){
    printf("Task 1 Started\n");
    vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);    
}

void serial_task2(void *parameters)
{
    while(1){
    printf("Task 2 Started\n");
    vTaskDelay(4000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void serial_task3(void *parameters)
{
    printf("Task 3 Started\n");
    vTaskDelay(6000/portTICK_PERIOD_MS);
    xTimerStart(timer1,0);
    vTaskDelete(NULL);
}

void app_main()
{
    BaseType_t res1,res2,res3;
    res1 = xTaskCreatePinnedToCore(serial_task1,"Task_1",4096,NULL,2,&task1,TASKCORE);
    if(res1!=pdPASS)
    {
        printf("task 1 not created\n");
    }
     res2 = xTaskCreatePinnedToCore(serial_task2,"Task_2",4096,NULL,4,&task2,TASKCORE);
    if(res2!=pdPASS)
    {
        printf("task 2 not created\n");
    }
     res3 = xTaskCreatePinnedToCore(serial_task3,"Task_3",4096,NULL,8,&task3,TASKCORE);
    if(res3!=pdPASS)
    {
        printf("task 3 not created\n");
    }
    timer1=xTimerCreate("Timer",(7000/portTICK_PERIOD_MS),pdTRUE,0,callbacktimer);
}
