#include "tScheduler.h"


/*************Simple implementation of Linked List*****************/
Node_t *Head = NULL;

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
  Node_t *ptr = Head;
  for (byte i = 0; i < nodePos; i++)
  {
    ptr = ptr -> next;
  }
  return ptr;
}
/****************************End of Linked List******************************/

Task::Task(int intervalSec, taskCb_t cb)
{
  _Cb = cb;
  _interval = intervalSec;
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

}
void Scheduler::addTask(Task *taskPtr)
{
  Head = addNode(Head, taskPtr);
}

Task *Scheduler::getCurrentTask()
{
  long interval;
  long currentTime;
  Node_t *ptr = Head;
  Task *task;
  do
  {
    currentTime = _timer();
    task = ptr -> task;

    if ((currentTime - task -> _prevTime) >= task -> _interval)
    {
      Serial.print(F("Time : ")); Serial.println(currentTime);
      task -> _prevTime = currentTime;
      return task;
    }
    ptr = ptr -> next;
  } while (ptr != NULL);

  return NULL;
}
void Scheduler::run()
{
  //  long interval;
  //  Node_t *ptr = Head;
  //  do
  //  {
  //    Serial.print(F("Time : "));
  //    Serial.println(ptr -> task -> _interval);
  //    ptr = ptr -> next;
  //  } while (ptr != NULL);
  //  //  Serial.println(_timer());
  //  Head ->task -> _Cb();
  //  Node_t *temp = getNode(1);
  //  temp -> task -> _Cb();

  Task *currentTask = getCurrentTask();
  if (currentTask)
  {
    currentTask -> _Cb();
  }
}

