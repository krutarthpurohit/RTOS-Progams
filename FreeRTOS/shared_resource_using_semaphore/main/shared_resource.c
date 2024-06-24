/* 
 * Author: Krutarth Purohit
 * 
 * In this program we use binary semaphore to share the resource systematically 
 * between two tasks: Task-A and Task-B to perforam their operation on it.
 * 
 * Try to change the values of vTaskDelay() in Task 1 and Task 2 and then observe the output.
 *  
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

// Define a binary semaphore
SemaphoreHandle_t xSemaphore;

// Shared resource variable
int sharedResource = 0;

// Task 1 function
void vTask1(void *pvParameters) 
{
    while (1) 
    {

        // Take the semaphore, it will empty the semaphore so no other task can get the access the shared resource until then wait in the block state
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
        {
            // Access the shared resource
            sharedResource++;
            printf("Task 1: Shared resource incremented to %d\n", sharedResource);
            // Release the semaphore
            xSemaphoreGive(xSemaphore); // Once the task is complete, the task will again fill the semaphore value before leaving so that other task can access the shared resource and execute its program
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// Task 2 function
void vTask2(void *pvParameters) 
{
    while (1) 
    {

        // Take the semaphore, it will empty the semaphore so no other task can get the access the shared resource until then wait in the block state
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) 
        {
            // Access the shared resource
            sharedResource--;
            printf("Task 2: Shared resource decremented to %d\n", sharedResource);
            // Release the semaphore
            xSemaphoreGive(xSemaphore); // Once the task is complete, the task will again fill the semaphore value before leaving so that other task can access the shared resource and execute its program
        }
        /* Higher the delay you give to task 2 more the time it will wait in block state
         * till then task 1 will get execuited and add the shared resource  */
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main() 
{
    // Create a binary semaphore
    xSemaphore = xSemaphoreCreateBinary(); 

    //Giving the value (assume '1') to the semaphore so it is filled
    xSemaphoreGive(xSemaphore);
    
    //since the semaphore is filled, the condition will become TRUE and Task 1 and Task 2 will be execuited
    if (xSemaphore != NULL) 
    {
        // Create Task 1
        xTaskCreate(vTask1, "Task 1", 2048, NULL, 2, NULL);
        // Create Task 2
        xTaskCreate(vTask2, "Task 2", 2048, NULL, 2, NULL);
    }
}
