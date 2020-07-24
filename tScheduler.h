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
    Task(int intervalSec, taskCb_t cb);
  private:
    taskCb_t _Cb;
    int _interval;
    int _prevTime;
    

};

class Scheduler
{
    friend class Task;
  public:
    void begin(uint32_t (*timer)(void) = NULL);
    void addTask(Task *taskPtr);
    void removeTask(Task *taskPtr);
    Task *getCurrentTask();
    void run();
  private:
    uint32_t (*_timer)(void);

    //  Task *_task;
};
#endif
