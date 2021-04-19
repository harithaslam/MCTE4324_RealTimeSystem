/**Reference: Digi-Key FreeRTOS
   FreeRTOS Stack Demo

   One task reads from Serial, constructs a message buffer, and the second
   prints the message to the console.

   Date: April 19, 2021
*/

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Task: Perform some task
void testTask(void *parameters) {

  // Loop forever
  while (1) {
    int a = 1;
    int b[100];

    //Do something with array so it's not optimized out by the compiler
    for (int i = 0 ; i < 100 ; i++) {
      b[i] = a + 1;
    }
    Serial.println(b[0]);

    //Print out remaining stack memory(words)
    Serial.print("High water mark (words): ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));

    //Print out number of free heap memory bytes before malloc
    Serial.print("Heap before malloc (words): ");
    Serial.println(xPortGetFreeHeapSize());
    int *ptr = (int*)pvPortMalloc(1024 * sizeof(int));

    //One way to prevent heap overflow is to check malloc output
    if ( ptr == NULL) {
      Serial.println("Not enough heap.");

    } else {

      //Do something with the memory so it's not optimized out by the compiler
      for (int i = 0; i < 1024 ; i++) {
        ptr[i] = 3;
      }
    }

    //Print out number of free heap memory bytes after malloc
    Serial.print("Heap before malloc (words): ");
    Serial.println(xPortGetFreeHeapSize());

    //Free up our allocated memory
    vPortFree(ptr);
   
    //Wait for a while
    vTaskDelay(273 / portTICK_PERIOD_MS);
  }
}

void setup() {

  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(5000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Memory Demo---");

  // Start Serial receive task
  xTaskCreatePinnedToCore(testTask,
                          "Test Task",
                          1500,
                          NULL,
                          1,
                          NULL,
                          app_cpu);


  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}
