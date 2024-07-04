#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#define TASKCORE 1
TaskHandle_t task1,task2;
int count = 0;
void serial_task1(void *parameters)
{
    while(1)
    {
        printf("INSIDE TASK 1\n");
        count--;
        printf("task 1 count = %d\n",count);
        if(count<0){
        printf("task 1 count = %d\n",count);
        count = 0;
         printf("going to task 2 resumed\n");
        vTaskResume(task2);
       
        }
    }
    
    vTaskDelete(task1);
}

void serial_task2(void *parameters)
{
    while(1)
    {
        printf("INSIDE TASK 2\n");
        count++;
        printf("task 2 count = %d\n",count);
        if(count == 5){
        printf("task 2 count = %d\n",count);
        printf("going to task 2 suspend\n");
        vTaskSuspend(task2);
        }
        
    }
   
    vTaskDelete(task2);
}

void app_main()
{
    BaseType_t res1,res2;
    res1 = xTaskCreatePinnedToCore(serial_task1,"TASK_1",2048,NULL,2,&task1,TASKCORE);
    if(res1 == pdPASS)
    {
        printf("task 1 created\n");
    }
    res2 = xTaskCreatePinnedToCore(serial_task2,"TASK_2",2048,NULL,4,&task2,TASKCORE);
    if(res2 == pdPASS)
    {
        printf("task 2 created\n");
    }
}
