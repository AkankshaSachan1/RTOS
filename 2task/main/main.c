#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#define TASKCORE 1
TaskHandle_t task1,task2;

void serial_task1(void *parameters)
{
    while(1)
    {
        printf("INSIDE TASK 1\n");
    }
    vTaskDelete(task1);
}

void serial_task2(void *parameters)
{
    while(1)
    {
        printf("INSIDE TASK 2\n");
    }
    vTaskDelete(task2);
}

void app_main()
{
    BaseType_t res1,res2;
    res1 = xTaskCreatePinnedToCore(serial_task1,"TASK_1",2048,NULL,8,&task1,TASKCORE);
    
    res2 = xTaskCreatePinnedToCore(serial_task2,"TASK_1",2048,NULL,8,&task2,TASKCORE);
    if(res1 == pdPASS)
    {
        printf("task 1 created\n");
    }
    if(res2 == pdPASS)
    {
        printf("task 2 created\n");
    }
}