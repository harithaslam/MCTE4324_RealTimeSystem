#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Settings
static const uint8_t msg_queue_len = 5; // max no. of queue can hold
//above queue is set as global for both task can access it

//Globals
static QueueHandle_t msg_queue;

//********************
//Tasks
void printMessages(void *parameter) {

  int item;// store value that we read //int is set as we want to sent integer val

  //Loop forever
  while (1) {

    //See if there's  a message in the queue(do not block)
    if (xQueueReceive(msg_queue, (void *)&item, 0) == pdTRUE) { //first parameter is the handle to the queue (global var)
      //2nd: address which is item (local var), queue item copied to //3rd: timeout
//      Serial.println(item);
    }
      Serial.println(item); //what happens if no new items received
    
    //Wait while trying again
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  //Configure Serial
  Serial.begin(115200);

  //Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(2000/ portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("--FreeRTOS Queue Demo--");

  //Create Queue
  msg_queue = xQueueCreate(msg_queue_len, sizeof(int)); //set our handle to the return value

  //Start print task
  xTaskCreatePinnedToCore(printMessages,
                          "Print Messages",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

}

void loop() {

  static int num = 0; //increase with each execution of loop

  //Try to add item to queue for 10 ticks, fail if queue is full
  if (xQueueSend(msg_queue, (void *)&num, 10) != pdTRUE) {    //Handle our queue
    Serial.println("Queue full"); //error message
  }
  num++;

  //Wait before trying again
  vTaskDelay (100 /portTICK_PERIOD_MS);
}
