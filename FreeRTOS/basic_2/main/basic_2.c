
/*          
 *                                          Basic Program
 * Author: Krutarth Purohit
 *
 * In this program, we create two different tasks and using FreeRTOS we do scheduling.
 * 
 */

/* OUTPUT: 
 * Task 1 is running
 * Task 2 is running
 * Task 1 is running
 * Task 2 is running
 * Task 1 is running
 * Task 2 is running
 * Task 1 is running
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"

/*
 * Defining the priority of both the task.
 * Task 2 has higher priority than Task 
 */
#define TASK_1_PRIORITY    (1U)
#define TASK_2_PRIORITY    (1U)

void vTask2(void* pvParameters)
{
    volatile unsigned long ulCount; 
    while( 1 ) 
    { 
        printf( "Task 2 is running\n" ); 
        for( ulCount = 0; ulCount < 1000; ulCount++ ) {  } 
    } 
} 

void vTask1(void* pvParameters)
{ 
    volatile unsigned long ulCount; 
    while( 1 ) 
    { 
        printf( "Task 1 is running\n" ); 
        for( ulCount = 0; ulCount < 1000; ulCount++ ) {  } 
    } 
} 

void app_main(void)
{ 
    xTaskCreate( vTask1, "Task 1", 1000, NULL, TASK_1_PRIORITY, NULL );
    xTaskCreate( vTask2, "Task 2", 1000, NULL, TASK_2_PRIORITY, NULL );
    // vTaskStartScheduler();
    for(;;);
}
