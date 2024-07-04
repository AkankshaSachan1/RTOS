#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"
#define core 1
TaskHandle_t task1,task2,task3,task4,task5;
QueueHandle_t msgq;

void single_task1(void *data)
{
    while(1)
    {
        printf("\n---------IN TASK1--------\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    vTaskDelete(NULL);
}
void single_task2(void *data)
{
    while(1)
    {
        printf("\n---------IN TASK2--------\n");
        vTaskDelay(pdMS_TO_TICKS(2000)); 
    }
    vTaskDelete(NULL);
}

void single_task3(void *data)
{
   while(1)
    {
        printf("\n---------IN TASK3--------\n");
        vTaskDelay(pdMS_TO_TICKS(5000)); 
    }
    vTaskDelete(NULL);
}

void single_task4(void *data)
{
    BaseType_t send;
    int pdata =100;
    while(1)
    {
        pdata++;
        printf("\n---------IN TASK 4---------\n");
        send=xQueueSend(msgq,&pdata,pdMS_TO_TICKS(1000));
        if(send==pdFALSE)
        {
           perror("Sending Failed\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }    
    vTaskDelete(NULL);
}

void single_task5(void *data)
{
    int buffer;
    BaseType_t rec=0;
    while(1)
    {
        printf("\n---------IN TASK5--------\n");
        rec=xQueueReceive(msgq,&buffer,pdMS_TO_TICKS(1000));
        if(rec==pdTRUE)
        {
            printf("Data Received from Task 4:%d\n",buffer);
        }
        else
        {
            printf("Error in receving data\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
    vTaskDelete(NULL);
}


void app_main()
{
    printf("inside the app_main\n");

   msgq = xQueueCreate(5,sizeof(int));
 

    if(xTaskCreatePinnedToCore(single_task1,"TASK1",4096,NULL,5,&task1,core)!=pdPASS){
        printf("task1 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task2,"TASK2",4096,NULL,6,&task2,core)!=pdPASS){
        printf("task2 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task3,"TASK3",4096,NULL,7,&task3,core)!=pdPASS){
        printf("task3 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task4,"TASK4",4096,NULL,8,&task4,core)!=pdPASS){
        printf("task4 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task5,"TASK5",4096,NULL,9,&task5,core)!=pdPASS){
        printf("task5 not created\n");
    }
   
      
}
