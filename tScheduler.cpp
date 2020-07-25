#include "tScheduler.h"


/*************Simple implementation of Linked List*****************/
Node_t *taskHead = NULL;
Node_t *queueHead = NULL;

Node_t *createNode();
Node_t *addNode(Node_t *head, Task *taskPtr);



Node_t *createNode()
{
  Node_t *temp = (Node_t*)malloc(sizeof(Node_t));
  temp -> next = NULL; //make next point to NULL
  return temp;
}
Node_t *addNode(Node_t *head, Task *taskPtr)
{
  Node_t *nodePtr;
  Node_t *temp = createNode();
  temp -> task = taskPtr;
  if (head == NULL)
  {
    //    Serial.println(F("it's head"));
    head = temp; //while linked list is empty
  }
  else
  {
    nodePtr = head;
    //    Serial.println(F("Not head"));
    //    Node_t *nodePtr;
    while (nodePtr -> next != NULL)
    {
      nodePtr = nodePtr -> next; //traverse the list until last node
    }
    nodePtr ->next = temp;  //previous last node next = current node pointer
  }

  return head;
}

Node_t *getNode(byte nodePos)
{
  Node_t *ptr = taskHead;
  for (byte i = 0; i < nodePos; i++)
  {
    ptr = ptr -> next;
  }
  return ptr;
}

byte getSize(Node_t *head)
{
  Node_t *p = head;
  byte counter = 0;
  while (p != NULL)
  {
    counter++;
    p = p -> next;
  }
  return counter;
}
/****************************End of Linked List******************************/

Task::Task(long interval, taskCb_t cb, byte priority)
{
  _Cb = cb;
  _interval = interval;
  _priority = priority;
  _prevTime = 0;
}

void Scheduler::begin(uint32_t (*timer)(void))
{
  if (timer == NULL)
  {
    _timer = millis;
  }
  else
  {
    _timer = timer;
  }

  _totalTasks = getSize(taskHead);
  Serial.print(F("Total Tasks: ")); Serial.println(_totalTasks);
  qPtr = (Task**)malloc(_totalTasks * sizeof(Task*));

  nullQBuf();
  //  Task **p = qPtr;
  //  for(byte i = 0; i<_totalTasks;i++)
  //  {
  //    *p = NULL;
  //    p++;
  ////    if(*qPtr == NULL)
  ////    {
  ////      Serial.println("NULL");
  ////    }
  //  }


  //  Serial.print(F("Task Size: "));Serial.println(sizeof(Task*));
  //  _queuePtr = (Task*)malloc(_totalTasks*sizeof(Task*));
  //
  //  Task *p = _queuePtr;
  //  for(byte i =0; i<_totalTasks; i++)
  //  {
  //    p = NULL;
  //    p++;
  //  }

}

void Scheduler::nullQBuf()
{
  Task **p = qPtr;
  for (byte i = 0; i < _totalTasks; i++)
  {
    *p = NULL;
    p++;
  }
}

void Scheduler::addTask(Task *taskPtr)
{
  taskHead = addNode(taskHead, taskPtr);
}

//Task *Scheduler::getCurrentTask()
//{
//  long interval;
//  long currentTime;
//  Node_t *ptr = taskHead;
//  Task *task;
//  do
//  {
//    currentTime = _timer();
//    task = ptr -> task;
//
//    if ((currentTime - task -> _prevTime) >= task -> _interval)
//    {
//      Serial.print(F("Time : ")); Serial.println(currentTime);
//      task -> _prevTime = currentTime;
//      return task;
//    }
//    ptr = ptr -> next;
//  } while (ptr != NULL);
//
//  return NULL;
//}

Task **Scheduler::getTaskQueue()
{
  Node_t *ptr = taskHead;
  Task **qP = qPtr;
  Task *task = NULL;
  
  long currentTime =  _timer();
  do
  {
    task = ptr -> task;
    if ((currentTime - task -> _prevTime) >= task -> _interval)
    {
      Serial.println(F("<-------------------Task added into queue"));
      task -> _prevTime = currentTime;
      *qP = task;
      qP++;
    }
    else
    {
      *qP = NULL;
    }

    ptr = ptr -> next;
  } while (ptr != NULL);
  return qPtr;
  //  do
  //  {
  //    currentTime = _timer();
  ////    currentTime = millis();
  //    task = ptr -> task;
  ////    Serial.print(F(" Millis :"));Serial.println(currentTime);
  ////    Serial.print(F("Prev Millis :"));Serial.println(task -> _prevTime);
  //    //    Serial.println(F("Counter"));
  //    if ((currentTime - task -> _prevTime) >= task -> _interval)
  //    {
  ////      Serial.println(F("<-------------------Task added into queue"));
  //      task -> _prevTime = currentTime;
  //      *qBuf = task;
  //      qBuf++;
  //    }
  //    ptr = ptr -> next;
  //  } while (ptr != NULL);
  //  return qptr;
}

void Scheduler::run()
{
  Task  **taskPtr = getTaskQueue();
  if (*taskPtr)
  {
    Task **prevTask = NULL;
//    byte tCounter = 0;
//    do
//    {
//      if(*taskPtr)
//      {
//        (*taskPtr) -> _Cb();
//      }
//      prevTask = taskPtr;
//      taskPtr++;
//      *prevTask = NULL;
//      tCounter++;
//    }while(tCounter <= _totalTasks);

    for ( byte i = 0; i < _totalTasks; i++)
    {
      prevTask = taskPtr;
      if (*taskPtr != NULL)
      {
        (*taskPtr) -> _Cb();
      }
      else
      {
        Serial.println(F("Null Pointer"));
      }
      taskPtr++;
      *prevTask = NULL;
    }
//    nullQBuf();
  }

  //  (*ptr) -> _Cb();


  //  if (*ptr)
  //  {
  //    Serial.println(F("<============Execution start===========>"));
  //    Task **prevPtr = NULL;
  //    byte taskCount = 0;
  //    do
  //    {
  //      (*ptr) -> _Cb();
  //      prevPtr = ptr;
  //      ptr++;
  //      *prevPtr = NULL;
  //      taskCount++;
  //    } while (*ptr);
  ////    nullQBuf();
  //  }

}

//  Serial.println(F("<============Execution start===========>"));
//  for( byte i = 0; i < _totalTasks; i++)
//  {
//    if(*ptr !=NULL)
//    {
//      Serial.println(F("NOT NULL"));
//    }
//  }
//  nullQBuf();

