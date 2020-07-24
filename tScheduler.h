#ifndef _T_SCHEDULER_
#define _T_SCHEDULER_
#include <Arduino.h>

typedef void (*taskCb_t)(void);

class Scheduler;
class Task;

typedef struct Node_t
{
  Task *task;
  Node_t *next;
};


class Task
{
    friend class Scheduler;
  public:
    Task(long interval, taskCb_t cb, byte priority = 0);
  private:
    taskCb_t _Cb;
    long _interval;
    long _prevTime;
    byte _priority;
    

};

class Scheduler
{
    friend class Task;
  public:
    void begin(uint32_t (*timer)(void) = NULL);
    void addTask(Task *taskPtr);
    void removeTask(Task *taskPtr);
    Node_t *getTaskQueue(Node_t *head);
    void run();
  private:
    uint32_t (*_timer)(void);
};
#endif
