#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define TASKCORE 1
int a=20,b=30;
int res=0;
TaskHandle_t task1,task2,task3;
void serial_task1(void *parameters)
{
    printf("Went to 1\n");
    vTaskSuspend(task1);
    while(1)
    {
        printf("Addition\n");
        res=a+b;
        printf("result =%d\n",res);
         vTaskResume(task2);    
    }
    vTaskDelete(task1);
}

void serial_task2(void *parameters)
{
    //vTaskSuspend(task2);
      printf("Went to 2\n");
    while(1)
    {   
        vTaskSuspend(task2);     
        printf("Substraction\n");
        res=res-a;
         printf("Result=%d\n",res);
           vTaskResume(task3);
           
    }          
    vTaskDelete(task2);
}
void serial_task3(void *parameters)
{
      printf("Went to 3\n");
    while(1)
    {
        vTaskResume(task1);
        vTaskSuspend(task3);
        printf("MULTIPLICATION\n");
         res=res*b;
         printf("Result=%d\n",res);
              
    }
    vTaskDelete(task3);
}

void app_main()
{
    BaseType_t res1,res2,res3;
    res1 = xTaskCreatePinnedToCore(serial_task1,"Task_1",4096,NULL,2,&task1,TASKCORE);
    if(res1==pdPASS)
    {
        printf("Addition*\n");
    }
     res2 = xTaskCreatePinnedToCore(serial_task2,"Task_2",4096,NULL,4,&task2,TASKCORE);
    if(res2==pdPASS)
    {
        printf("substraction*\n");
    }
     res3 = xTaskCreatePinnedToCore(serial_task3,"Task_3",4096,NULL,8,&task3,TASKCORE);
    if(res3==pdPASS)
    {
        printf("Multiplication*\n");
    }
}