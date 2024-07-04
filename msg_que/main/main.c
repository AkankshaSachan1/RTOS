#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"
#define core 1
TaskHandle_t task1_handle,task2_handle,task3_handle,task4_handle,task5_handle;
QueueHandle_t msgq;

void single_task1(void *data)
{
    printf("Inside task1\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    vTaskDelete(NULL);
}

void single_task2(void *data)
{
    printf("Inside task2\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    vTaskDelete(NULL);
}

void single_task3(void *data)
{
    printf("Inside task3\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
    vTaskDelete(NULL);
}

void single_task4(void *data)
{
    int temp = 100;
    printf("task4 started\n");
while(1)
{   
    temp++;
  
    xQueueSend(msgq,&temp,pdMS_TO_TICKS(5000));
    vTaskDelay(pdMS_TO_TICKS(1000));
}
    vTaskDelete(NULL);
}

void single_task5(void *data)
{
    int rcv_data;
    printf("task5 started\n");
while(1)
{   
    xQueueReceive(msgq,&rcv_data,portMAX_DELAY);
    printf("task5 received data = %d\n",rcv_data);
    vTaskDelay(pdMS_TO_TICKS(1000));
   }
    vTaskDelete(NULL);
}

void app_main()
{
    printf("inside the app_main\n");

   msgq = xQueueCreate(5,sizeof(int));
 

    if(xTaskCreatePinnedToCore(single_task1,"TASK1",2048,NULL,5,&task1_handle,core)!=pdPASS){
        printf("task1 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task2,"TASK2",2048,NULL,6,&task2_handle,core)!=pdPASS){
        printf("task2 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task3,"TASK3",2048,NULL,7,&task3_handle,core)!=pdPASS){
        printf("task3 not created\n");
    }
    xTaskCreatePinnedToCore(single_task4,"TASK4",2048,NULL,8,&task4_handle,core);
    xTaskCreatePinnedToCore(single_task5,"TASK5",2048,NULL,9,&task5_handle,core);

  
}