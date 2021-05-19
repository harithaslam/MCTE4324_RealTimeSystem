In this queue challenge, the LED blinks at the rate based on the delay apply on serial input. By using the queue feauture in FreeRTOS, we use xQueueCreate to create 2 queues with the size of 5
1. Creating queue capable of containing 5 integer values. (delay_queue_len)
2. Creating queue capable of containing 5 pointers to Message structures. (msg_queue_len)
