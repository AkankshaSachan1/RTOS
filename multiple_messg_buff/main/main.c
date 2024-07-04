#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/message_buffer.h"

#define TASKCORE 1

TaskHandle_t task1,task2;
MessageBufferHandle_t msg;
 

void serial_task1(void *data)
{
   // char buffer[] = "HELLO AKANKSHA ";
   // while(1){
     printf("Inside task1\n");
     printf("task1 :Data sent\n");
     xMessageBufferSend(msg,"HELLO\n",7,pdMS_TO_TICKS(10000));
     xMessageBufferSend(msg,"AKANKSHA\n",10,pdMS_TO_TICKS(20000));
     xMessageBufferSend(msg,"CDAC\n",6,pdMS_TO_TICKS(30000));
     printf("data sent\n");
    //}
     vTaskDelete(NULL);      
}

void serial_task2(void *data)
{
    size_t st=0;
     char rcv_buff[200];
     printf("Inside task 2\n");
      while(1)
       {
        printf("Requesting data\n");
        st= xMessageBufferReceive(msg,rcv_buff,200,portMAX_DELAY);
         printf("Task2: data received is %s of bytes %d\n",rcv_buff,st);
        // st= xMessageBufferReceive(msg,rcv_buff,200,pdMS_TO_TICKS(20000));
        // printf("Task2: data received is %s of bytes %d\n",rcv_buff,st);
        // st= xMessageBufferReceive(msg,rcv_buff,200,pdMS_TO_TICKS(30000));
        // printf("Task2: data received is %s of bytes %d\n",rcv_buff,st);
     }
      vTaskDelete(NULL);      
}

void app_main()
{
    BaseType_t res1,res2;
    msg=xMessageBufferCreate(50);
   
   
    printf("Inside app_main\n");
    res1 = xTaskCreatePinnedToCore(serial_task1,"Task_1",4096,NULL,4,&task1,TASKCORE);
    if(res1!=pdPASS)
    {
        printf("task 1 not created\n");
    }
     res2 = xTaskCreatePinnedToCore(serial_task2,"Task_2",4096,NULL,8,&task2,TASKCORE);
    if(res2!=pdPASS)
    {
        printf("task 2 not created\n");
    }
     
}
