/*  Date: March 29, 2021
    Author: Shawn Hymel
    License: OBSD
*/

//Use only core 1 for demo
#if CCONFIG_FREETOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

//Some string to print
//const char msg[] = "A Roadrunner Run on the Running Track during Running Event.";
const char msg[] = "Barladeer brig Arr booty rum.";

//Task handles to control third task 
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

//************************************
//Tasks

///Task: print to Serial Terminal with lower priority
void startTask1(void *parameter) {

  //Count number of characters in  string
  int msg_len = strlen(msg);

  //Print string to Serial Terminal
  while(1)  {
    Serial.println();
    for (int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);  //put into a block state for 1 second
  }
}

//Task: print to Serial Terminatl with higher priority
void startTask2(void *parameter)  {
  while(1)  {
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

//*************************
// Main (runs as its own task with priority 1 on 1 core)

void setup() {
  // Configure Serial (go slow so we can watch the preemption)
  Serial.begin(300);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Task Demos---");

  //Print self priority
  Serial.print("Setup and loop task running on core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.println(uxTaskPriorityGet(NULL));

  //Task to run forever
    xTaskCreatePinnedToCore(startTask1,   // Call Function of the task
                            "Task1",      // Name of task
                            1024,         // Stack size(bytes in ESP32, words in FreeRTOS)
                            NULL,         // Parameter to pass to function
                            1,            // Task priority
                            &task_1,      // Task handle
                            app_cpu);     // Run on one core
                            
  //Task to run forever with high priority 
    xTaskCreatePinnedToCore(startTask2,   // Call Function of the task
                            "Task2",      // Name of task
                            1024,         // Stack size(bytes in ESP32, words in FreeRTOS)
                            NULL,         // Parameter to pass to function
                            2,            // Task priority
                            &task_2,      // Task handle
                            app_cpu);     // Run on one core
}

void loop() {
  // Suspend the higher priority task for some intervals
  for (int i = 0; i < 3; i++) {
    vTaskSuspend(task_2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskResume(task_2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  // Delete the lower priority task
  if (task_1 != NULL) {
    vTaskDelete(task_1);
    task_1 = NULL;
  }
}
