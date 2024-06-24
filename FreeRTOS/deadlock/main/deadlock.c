
/*          
 *                                          Deadlock Problem
 * Author: Krutarth Purohit
 *
 * This program demonstrates the concept of deadlock condition that occur in the FreeRTOS program. 
 * Deadlock is the concept in which tasks are blocked into the waiting state because of one another.
 * 
 * Here Task 1 takes the mutex-1 but only releases it if it has mutex-2.
 * And Task 2 takes the mutex-2 but only releases it if it has mutex-1.
 * 
 * Now, here deadlock has occured as both of the tasks are waiting for one another to release eachother's mutex, 
 * but they would not be able to do so as now both the tasks are in blocked state.
 * 
 * Solution to deadlock:
 * In particular,  it is normally bad practice for a task to wait indefinitely (without a time out) to obtain a mutex. 
 * Instead, use a time out that is a little longer than the maximum time it is expected to have to wait for the mutex.
 * 
 */

/* OUTPUT: 
 * I (331) main_task: Calling app_main()
 * Task 1 has acquired mutex 1
 * I (331) main_task: Returned from app_main()
 * Task 2 has acquired mutex 2
 *  ---Deadlock occured as program won't proceed further---
 * 
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define TASK1_PRIORITY  1
#define TASK2_PRIORITY  1

SemaphoreHandle_t xMutex_1;                     //Mutex-1 for task-1
SemaphoreHandle_t xMutex_2;                     //Mutex-2 for task-2

void task1(void *pvParameters) 
{
    while(1) 
    {
        if (xSemaphoreTake(xMutex_1, (TickType_t)10) == pdTRUE)             //Take mutex-1 
        {
            printf("Task 1 has acquired mutex 1\n");
            // Do critical section work here
            vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate some work

            /* This task waits indefinitely to aquire mutex-2 so it can release mutex-1 */
            if (xSemaphoreTake(xMutex_2, (TickType_t)10) == pdTRUE)         //release mutex-1 only if it has mutex-2
            {
                /* code */
                printf("Task 1 releasing mutex 2\n");
                xSemaphoreGive(xMutex_1);
            }

        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Some delay before trying again
    }
}

void task2(void *pvParameters) {
    while(1) {
        if (xSemaphoreTake(xMutex_2, (TickType_t)10) == pdTRUE)             //Take mutex-2
        {
            printf("Task 2 has acquired mutex 2\n");
            // Do critical section work here
            vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate some work

            /* This task waits indefinitely to aquire mutex-1 so it can release mutex-2 */
            if (xSemaphoreTake(xMutex_1, (TickType_t)10) == pdTRUE)         //release mutex-2 only if it has mutex-1
            {
                /* code */
                printf("Task 2 releasing mutex\n");
                xSemaphoreGive(xMutex_2);
            }
            
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Some delay before trying again
    }
}
void app_main()
{
    xMutex_1 = xSemaphoreCreateMutex();
    xMutex_2 = xSemaphoreCreateMutex();

    if ((xMutex_1 != NULL) && (xMutex_2 != NULL))
    {
        xTaskCreate(task1, "Task 1", 2048, NULL, TASK1_PRIORITY, NULL);
        xTaskCreate(task2, "Task 2", 2048, NULL, TASK2_PRIORITY, NULL);
    }
    else
    {
        printf("Failed to create mutex\n");
    }
}
