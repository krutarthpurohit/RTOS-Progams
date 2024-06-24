
/*          
 *                                          Basic Program
 * Author: Krutarth Purohit
 *
 * In this program, we create two different tasks and using FreeRTOS we do scheduling.
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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"

/*
 * Defining the priority of both the task.
 * Task 2 has higher priority than Task 
 */
#define TASK_1_PRIORITY    (1U)
#define TASK_2_PRIORITY    (2U)

void vTask2(void* pvParameters)
{
    while( 1 ) 
    { 
        printf( "Task 2 is running\n" ); 
        vTaskDelay(100);

    } 
} 

void vTask1(void* pvParameters)
{ 
    while( 1 ) 
    { 
        printf( "Task 1 is running\n" ); 
        vTaskDelay(100);
    
    } 
} 

void app_main(void)
{ 
    xTaskCreate( vTask1, "Task 1", 1000, NULL, TASK_1_PRIORITY, NULL );
    xTaskCreate( vTask2, "Task 2", 1000, NULL, TASK_2_PRIORITY, NULL );
}
