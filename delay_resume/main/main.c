#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define TASKCORE 1
TaskHandle_t task1,task2;
int count = 0;

void serial_task1(void *parameters)
{
    printf("in task1\n");
    while(1){
        
    vTaskResume(task2);
    
   
   }
    vTaskDelete(task1);
}

void serial_task2(void *parameters)
{
    printf("in task 2\n");
    while(1){
        
        //count++;
      //  printf("count = %d\n",count);
        vTaskSuspend(task2);
        printf("Waiting\n");
        vTaskDelay(15000/portTICK_PERIOD_MS);

    
   }
    vTaskDelete(task2);
}



void app_main()
{
    // BaseType_t res1,res2;
   xTaskCreatePinnedToCore(serial_task1,"TASK_1",2048,NULL,2,&task1,TASKCORE);
   xTaskCreatePinnedToCore(serial_task2,"TASK_2",2048,NULL,4,&task2,TASKCORE);
  
   
}