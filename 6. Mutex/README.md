MUTEX (Mutual Exclusion)

Mutex act like a lock (part of the usage) where it shared multiple processors.

Mutex solves race condition situation. (See README.md in Race Condition file)
It excluedes other tasks from entering a critical section. 

RACE CONDITION:
It is the event when task B run and interrupt task A, causing task A did not finish to increase and writing back to it.

CRITICAL SECTION:
It is the section or the function that executes task. It is called critical as it must be executed to its entirety before executing another task.
