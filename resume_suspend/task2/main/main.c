#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define TASKCORE 1
TaskHandle_t task1,task2,task3;
void serial_task1(void *parameters)
{
    int count=0;

    while(1){
    printf("task 1 started\n");
    count++;
    printf("Count in task 1 = %d\n",count);
    if(count==4)
    {
    vTaskResume(task2);
    }
    if(count==6){
        count =0;
    vTaskResume(task3);
    }
    }
    vTaskDelete(task1);
}

void serial_task2(void *parameters)
{
    int count=0;

    while(1){
        printf("Hello in task 2\n");
    vTaskSuspend(task2);
    printf("In task 2\n");
    }
     vTaskDelete(task2);
}

void serial_task3(void *parameters)
{
    int count=0;

    while(1){
        printf("bye in task3\n");
    vTaskSuspend(task3);
    printf("In task 3\n");
    }
     vTaskDelete(task3);
}

void app_main()
{
    BaseType_t res1,res2,res3;
    res1 = xTaskCreatePinnedToCore(serial_task1,"TASK_1",4096,NULL,2,&task1,TASKCORE);
    if(res1==pdPASS)
    {
        printf("Task 1 created\n");
    }
    res2 = xTaskCreatePinnedToCore(serial_task2,"TASK_2",4096,NULL,4,&task2,TASKCORE);
    if(res2==pdPASS)
    {
        printf("Task 2 created\n");
    }
    res3 = xTaskCreatePinnedToCore(serial_task3,"TASK_3",4096,NULL,8,&task3,TASKCORE);
    if(res3==pdPASS)
    {
        printf("Task 3 created\n");
    }
}