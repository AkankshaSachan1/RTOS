#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define TASKCORE 1

TaskHandle_t task1,task2,task3;
void serial_task1(void *parameters)
{
    int count =0;
  vTaskSuspend(task1);
    while(1)
    {
        count++;
        if(count>5)
        {
           printf("Task 2 resumed\n");
           vTaskResume(task2);
           vTaskSuspend(task1);
           count =0;
        }
        printf("Task 1 is running\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(task1);
}

void serial_task2(void *parameters)
{
    int count =0;
    vTaskSuspend(task2);
    while(1)
    {
        
        count++;
        if(count>5)
        {
        	printf("Task 3 resumed\n");
           vTaskResume(task3);
           vTaskSuspend(task2);
           count =0;
        }
        printf("Task 2 is running\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(task2);
}
void serial_task3(void *parameters)
{
    int count =0;
   // vTaskSuspend(task3);
    while(1)
    {
        count++;
        if(count>5)
        {
        	printf("Task 1 resumed\n");
           vTaskResume(task1);
          
           vTaskSuspend(task3);
           count =0;
        }
        printf("Task 3 is running\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(task3);
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
}
