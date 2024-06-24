#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#define HIGH 1
#define LOW 0

// Task 1 function
void vTask1(void *pvParameterss) 
{
    while (1) 
    {
       gpio_set_level( GPIO_NUM_5 , LOW);
       vTaskDelay(1000);
       gpio_set_level( GPIO_NUM_5 , HIGH);
       vTaskDelay(100);
    }
}

// Task 2 function
void vTask2(void *pvParameters) 
{
    while (1) 
    {
        gpio_set_level( GPIO_NUM_2 , LOW);
        vTaskDelay(200);
        gpio_set_level( GPIO_NUM_2 , HIGH);
        vTaskDelay(200);
        // vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main() 
{
    gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    
    // Create Task 1
    xTaskCreate(vTask1, "Task 1", 2048, NULL, 2, NULL);
    // Create Task 2
    // xTaskCreate(vTask2, "Task 2", 2048, NULL, 2, NULL);
    // vTask1();

    
}
