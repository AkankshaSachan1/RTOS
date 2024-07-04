#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/timers.h"
#define TASKCORE 1
TaskHandle_t task;
TimerHandle_t timer;
int count = 0;
void timer_callback(TaskHandle_t timer)
{
    printf("timer start\n");
   
}

void task_call(void *parameter)
{
   
    printf("Task started\n");
    printf("timer is created\n");
  //  while(1){
        count=xTimerStart(timer,0);
        printf("count started\n");
         vTaskDelay(pdMS_TO_TICKS(10000));
        xTimerStop(timer,0);
           
         printf("timer stop\n");
  //  }
           
    vTaskDelete(task);
}

void app_main()
{
    BaseType_t res;
    printf("inside the main task\n");

res = xTaskCreatePinnedToCore(task_call,"TIMER_TASK",1024,NULL,2,&task,TASKCORE);
if(res != pdPASS)
{
    printf("task not created\n");
}

timer = xTimerCreate("TIMER",(pdMS_TO_TICKS(30000)),pdTRUE,NULL,timer_callback);

}
