#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/queue.h"
#define core 1
TaskHandle_t task1_handle,task2_handle,task3_handle,task4_handle;
QueueHandle_t msgq;

void single_task1(void *data)
{
    int temp = 100;
    printf("task1 started\n");
while(1)
{   
    temp++;
   // printf("task1 send data:\n");
   
    if(xQueueSend(msgq,&temp,pdMS_TO_TICKS(5000))!=pdPASS){
        printf("Error sending message\n");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
}
    vTaskDelete(NULL);
}
void single_task2(void *data)
{
    int humd = 200;
    printf("task2 started\n");
while(1)
{   
    humd++;
   // printf("task2 send data:\n");
    xQueueSend(msgq,&humd,pdMS_TO_TICKS(5000));
    
    vTaskDelay(pdMS_TO_TICKS(1000));
}
    vTaskDelete(NULL);
}

void single_task3(void *data)
{
    int rcv_data;
   //  vTaskSuspend(task3_handle);
    int count = 0;
    printf("task3 started\n");
while(1)
{   
    count++;
    xQueueReceive(msgq,&rcv_data,portMAX_DELAY);
    printf("task3 received data = %d\n",rcv_data);
    
    if(count > 20){
        count = 0;
    vTaskResume(task4_handle);
     }
    vTaskDelay(pdMS_TO_TICKS(1000));
   }
    vTaskDelete(NULL);
}

void single_task4(void *data)
{
    int buff;
    printf("task4 started\n");
    int count = 0;
    while(1){
        count++;
        xQueueReceive(msgq,&buff,portMAX_DELAY);
         printf("task4 received data = %d\n",buff);
        if(count>10){
            //vTaskResume(task3_handle);
            count = 0;
            vTaskSuspend(task4_handle);
            
       }
        vTaskDelay(pdMS_TO_TICKS(1000));
    
    }
    vTaskDelete(NULL);
}
void app_main()
{
    printf("inside the app_main\n");

   msgq = xQueueCreate(5,sizeof(int));
 

    if(xTaskCreatePinnedToCore(single_task1,"TASK1",4096,NULL,5,&task1_handle,core)!=pdPASS){
        printf("task1 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task2,"TASK2",4096,NULL,3,&task2_handle,core)!=pdPASS){
        printf("task2 not created\n");
    }
    if(xTaskCreatePinnedToCore(single_task3,"TASK3",4096,NULL,8,&task3_handle,core)!=pdPASS){
        printf("task3 not created\n");
    }
    xTaskCreatePinnedToCore(single_task4,"TASK4",2048,NULL,9,&task4_handle,core);
printf("End of app_main\n");
}