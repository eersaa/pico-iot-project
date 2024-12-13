#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define MAIN_LED_DELAY 800

static void led_task(void *pvParameters);
static void start_tasks();

static void prvSetupHardware( void );

/* Prototypes for the standard FreeRTOS callback/hook functions implemented
within this file. */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

/*-----------------------------------------------------------*/

void vLaunch( void)
{
    
    start_tasks();
}

int main( void )
{
    /* Configure the hardware ready to run the demo. */
    prvSetupHardware();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    printf("%s on core 0:\n", rtos_name);
    vLaunch();

    return 0;
}

void start_tasks() {
    // Create Your Task
    xTaskCreate(
        led_task,    // Task to be run
        "LED_TASK",  // Name of the Task for debugging and managing its Task Handle
        1024,        // Stack depth to be allocated for use with task's stack (see docs)
        NULL,        // Arguments needed by the Task (NULL because we don't have any)
        1,           // Task Priority - Higher the number the more priority [max is (configMAX_PRIORITIES - 1) provided in FreeRTOSConfig.h]
        NULL         // Task Handle if available for managing the task
    );

    // Should start you scheduled Tasks (such as the LED_Task above)
    vTaskStartScheduler();

    while (true) {
        // Your program should never get here
    };
}

void led_task(void *pvParameters) {
    // bool is_connected = true;
    // if (cyw43_arch_init()) {
    //     printf("WiFi init failed\n");
    //     is_connected = false;
    // }

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        printf("LED tuned ON!\n");
        vTaskDelay(MAIN_LED_DELAY);  // Delay by TICKS defined by FreeRTOS priorities
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        printf("LED turned OFF\n");
        vTaskDelay(MAIN_LED_DELAY);
    }
}

/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    volatile size_t xFreeHeapSpace;

    /* This is just a trivial example of an idle hook.  It is called on each
    cycle of the idle task.  It must *NOT* attempt to block.  In this case the
    idle task just queries the amount of FreeRTOS heap that remains.  See the
    memory management section on the http://www.FreeRTOS.org web site for memory
    management options.  If there is a lot of heap memory free then the
    configTOTAL_HEAP_SIZE value in FreeRTOSConfig.h can be reduced to free up
    RAM. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    /* Remove compiler warning about xFreeHeapSpace being set but never used. */
    ( void ) xFreeHeapSpace;
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
    ;
}
