#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/stream_buffer.h"
#define core 1
TaskHandle_t task1_handle,task2_handle;
StreamBufferHandle_t sb_msg;

void serial_task1(void *data)
{
    printf("TASK1 started\n");
    
    printf("Task1 sending the message\n");
    xStreamBufferSend(sb_msg,"HELLO\n",6,pdMS_TO_TICKS(20000));
    xStreamBufferSend(sb_msg,"AKANKSHA\n",9,pdMS_TO_TICKS(20000));
    xStreamBufferSend(sb_msg,"CDAC\n",6,pdMS_TO_TICKS(20000));
    printf("Task1 finished sending message\n");
    vTaskDelete(NULL);

}

void serial_task2(void *data)
{
    unsigned char rcv_buff[200];
    size_t nobytes = 0;
    printf("Task2 started\n");
while(1){
    printf("task2 request data to receive\n");
    nobytes = xStreamBufferReceive(sb_msg,rcv_buff,21,pdMS_TO_TICKS(20000));
    printf("TASK2 received data = %s, data in bytes = %d\n",rcv_buff,nobytes);
}
    vTaskDelete(NULL);

}
void app_main()
{
    printf("Inside app_main\n");

    sb_msg = xStreamBufferCreate(200,21);

    xTaskCreatePinnedToCore(serial_task1,"TASK1",2048,NULL,2,&task1_handle,core);
    xTaskCreatePinnedToCore(serial_task2,"TASK2",2048,NULL,2,&task2_handle,core);
}