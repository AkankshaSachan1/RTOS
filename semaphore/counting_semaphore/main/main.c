#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#define TASKCORE 1
TaskHandle_t task1,task2,task3,task4;
SemaphoreHandle_t mysema;

void serial_task1(void *data)
{
    //while(1){
     printf("Inside task1\n");
     printf("task1 requesting data\n");
     xSemaphoreTake(mysema,pdMS_TO_TICKS(20000));
     printf("Task 1 got the data\n");
     vTaskDelay(portMAX_DELAY);
     xSemaphoreGive(mysema);
     printf("data sent to task 1\n");
    //}
     vTaskDelete(NULL);      
}

void serial_task2(void *data)
{
    //while(1){
     printf("Inside task2\n");
     printf("task2 requesting data\n");
     xSemaphoreTake(mysema,pdMS_TO_TICKS(20000));
     printf("Task 2 got the data\n");
     vTaskDelay(portMAX_DELAY);
     xSemaphoreGive(mysema);
     printf("data sent to task 2\n");
    //}
     vTaskDelete(NULL);      
}

void serial_task3(void *data)
{
    //while(1){
     printf("Inside task3\n");
     printf("task3 requesting data\n");
     xSemaphoreTake(mysema,pdMS_TO_TICKS(20000));
     printf("Task 3 got the data\n");
     vTaskDelay(portMAX_DELAY);
     xSemaphoreGive(mysema);
     printf("data sent to task 3\n");
    //}
     vTaskDelete(NULL);      
}

void serial_task4(void *data)
{
    //while(1){
     printf("Inside task4\n");
     printf("task4 requesting data\n");
     xSemaphoreTake(mysema,pdMS_TO_TICKS(20000));
     printf("Task 4 got the data\n");
     vTaskDelay(portMAX_DELAY);
     xSemaphoreGive(mysema);
     printf("data sent to task 4\n");
    //}
     vTaskDelete(NULL);      
}
void app_main()
{
    BaseType_t res1,res2,res3,res4;
    mysema=xSemaphoreCreateCounting(10,1);

    printf("Inside app_main\n");
    res1 = xTaskCreatePinnedToCore(serial_task1,"Task_1",4096,NULL,4,&task1,TASKCORE);
    if(res1!=pdPASS)
    {
        printf("task 1 not created\n");
    }
    res2 = xTaskCreatePinnedToCore(serial_task2,"Task_2",4096,NULL,4,&task2,TASKCORE);
    if(res2!=pdPASS)
    {
        printf("task 2 not created\n");
    }
    res3 = xTaskCreatePinnedToCore(serial_task3,"Task_3",4096,NULL,4,&task3,TASKCORE);
    if(res3!=pdPASS)
    {
        printf("task 3 not created\n");
    }
    res4 = xTaskCreatePinnedToCore(serial_task4,"Task_4",4096,NULL,4,&task4,TASKCORE);
    if(res4!=pdPASS)
    {
        printf("task 4 not created\n");
    }
     
}
