#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Define a counting semaphore
SemaphoreHandle_t xSemaphore;

// Shared resource variable
int sharedResource = 0;

// Task 1 function
void vTask1(void *pvParameters) 
{
    while (1) 
    {
        // Take the semaphore
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
        {
            // Access the shared resource
            sharedResource++;
            printf("Task 1: Shared resource incremented: %d\n", sharedResource);
            // Release the semaphore
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// Task 2 function
void vTask2(void *pvParameters) 
{
    while (1) 
    {
        // Take the semaphore
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
        {
            // Access the shared resource
            sharedResource--;
            printf("Task 2: Shared resource decremented: %d\n", sharedResource);
            // Release the semaphore
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main() 
{
    // Create a counting semaphore with an initial count of 1
    xSemaphore = xSemaphoreCreateCounting(10, 0);
    xSemaphoreGive(xSemaphore);
    
    if (xSemaphore != NULL) 
    {
        // Create Task 1
        xTaskCreate(vTask1, "Task 1", 2048, NULL, 2, NULL);
        // Create Task 2
        xTaskCreate(vTask2, "Task 2", 2048, NULL, 2, NULL);
    }
}
