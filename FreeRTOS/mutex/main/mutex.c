#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define TASK1_PRIORITY  1
#define TASK2_PRIORITY  1

SemaphoreHandle_t xMutex;

void task1(void *pvParameters) 
{
    while(1) 
    {
        if (xSemaphoreTake(xMutex, (TickType_t)10) == pdTRUE)  
        {
            xSemaphoreTake(xMutex, (TickType_t)10);
            printf("Task 1 has acquired mutex\n");
            // Do critical section work here
            vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate some work
            printf("Task 1 releasing mutex\n");
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Some delay before trying again
    }
}
void task2(void *pvParameters) 
{
    while(1) 
    {
        if (xSemaphoreTake(xMutex, (TickType_t)10) == pdTRUE) 
        {
            xSemaphoreTake(xMutex, (TickType_t)10);
            printf("Task 2 has acquired\n");
            // Do critical section work here
            vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate some work
            printf("Task 2 releasing mutex\n");
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Some delay before trying again
    }
}
void app_main()
{
    xMutex = xSemaphoreCreateMutex();

    if (xMutex != NULL)
    {
        xTaskCreate(task1, "Task 1", 2048, NULL, TASK1_PRIORITY, NULL);
        xTaskCreate(task2, "Task 2", 2048, NULL, TASK2_PRIORITY, NULL);
    }
    else
    {
        printf("Failed to create mutex\n");
    }
}
