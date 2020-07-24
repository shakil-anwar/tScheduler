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
  while(p != NULL)
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

  Serial.print(F("Total Tasks: "));Serial.println(getSize(taskHead));

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
Node_t *Scheduler::getTaskQueue(Node_t *head)
{
  //  Serial.println(F("<---------Start------------------->"));
  Node_t *ptr = taskHead;
  long currentTime;
  Task *task;

  do
  {
    currentTime = _timer();
    task = ptr -> task;
    //    Serial.println(F("Counter"));
    if ((currentTime - task -> _prevTime) >= task -> _interval)
    {
//      Serial.println(F("Task added into queue"));
      head = addNode(head, task);
      task -> _prevTime = currentTime;
    }
    ptr = ptr -> next;

  } while (ptr != NULL);
  //  Serial.println(F("<---------End------------------->"));
  return head;
}

void Scheduler::run()
{
  //  long interval;
  //  Node_t *ptr = taskHead;
  //  do
  //  {
  //    Serial.print(F("Time : "));
  //    Serial.println(ptr -> task -> _interval);
  //    ptr = ptr -> next;
  //  } while (ptr != NULL);
  //  //  Serial.println(_timer());
  //  taskHead ->task -> _Cb();
  //  Node_t *temp = getNode(1);
  //  temp -> task -> _Cb();


  Node_t *qPtr = getTaskQueue(queueHead);
  if (qPtr)
  {
    Serial.println(F("<============Execution start===========>"));
    Serial.print(F("Queued Tasks: "));Serial.println(getSize(qPtr));
    do
    {
//      Serial.println(F("<---------Task----------->"));
      qPtr -> task -> _Cb();     
      Node_t *lastPtr = qPtr;
      qPtr = qPtr -> next;
      free(lastPtr);
    } while (qPtr != NULL);
    queueHead = NULL;
  }

}

