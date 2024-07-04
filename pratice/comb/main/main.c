#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"
#define core 1
TaskHandle_t task1,task2,task3;
TimerHandle_t tim;
QueueHandle_t msgq;
SemaphoreHandle_t sh;

void timercallback(TimerHandle_t xTimer)
{
    char buff[9]="Akanksha";
    printf("In timer callback function\n");
    xQueueSend(msgq,&buff,portMAX_DELAY);
    xSemaphoreGive(sh);
}

void single_task1(void *data)
{
    char buff[10];
    printf("\n------In Task1-------\n");
    xSemaphoreTake(sh,portMAX_DELAY);
    xQueueReceive(msgq,&buff,portMAX_DELAY);
    printf("Message =%s\n",buff);
    vTaskResume(task3);
    vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelete(NULL);
}
void single_task2(void *data)
{
    printf("\n-----In Task2----\n");
    tim=xTimerCreate("Timer1",pdMS_TO_TICKS(8000),pdFALSE,NULL,timercallback);
    BaseType_t tim1=xTimerStart(tim,0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    printf("After delay 3 secs\n");
    vTaskDelete(NULL);
}

void single_task3(void *data)
{
   vTaskSuspend(task3);
   printf("\n------In Task 3------\n");
   vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelete(NULL);
}


void app_main()
{
    printf("inside the app_main\n");

     msgq = xQueueCreate(5,64);
     vSemaphoreCreateBinary(sh);

    if(xTaskCreatePinnedToCore(single_task1,"TASK1",4096,NULL,9,&task1,core)!=pdPASS){
        printf("task1 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task2,"TASK2",4096,NULL,6,&task2,core)!=pdPASS){
        printf("task2 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task3,"TASK3",4096,NULL,4,&task3,core)!=pdPASS){
        printf("task3 not created\n");
    }
}      
     
