This is the Introduction for FreeRTOS Timer

In the code presented, there are two type of timers, 1: one-shot 2: auto-reload. By setting the pdTRUE (auto-reload) with TimerID to 1, the serial prints will continuosly updating the auto reload timer while the one-shot timer once.

Note that: the time for the auto-reload timer to be printed on serial monitor can be change from every seconds to every ticks that you want by changing period of timer (1000/ portTICK_PERIOD_MS)
