#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>
#define TASKCORE 1
TaskHandle_t task1;
TimerHandle_t timer1;
void timer_callback(TimerHandle_t xTimer)
{
    printf("Timer fired\n");
}
void serial_task(void *data)
{
    
    printf("timer create\n");
    timer1=xTimerCreate("one_shot_timer",(5000/portTICK_PERIOD_MS),pdTRUE,0,timer_callback);
    printf("Starting the timer\n");
    xTimerStart(timer1,0);
    
    vTaskDelete(task1);
   
}

void app_main()
{
    BaseType_t res1;
    printf("Inside app_main\n");
    res1 = xTaskCreatePinnedToCore(serial_task,"Task_1",4096,NULL,2,&task1,TASKCORE);
    if(res1!=pdPASS)
    {
        printf("task 1 not created\n");
    }
     
}
