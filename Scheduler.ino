#include "tScheduler.h"


void func1()
{
  Serial.println(F("Task One Done"));
}

void func2()
{
  Serial.println(F("Task Two Done"));
}

void func3()
{
  Serial.println(F("Task Three Done"));
}
Task task1(5000, &func1);
Task taks2(5000, &func2);
Task task3(5000, &func3);

Scheduler scheduler;
void setup()
{
  Serial.begin(115200);
  scheduler.addTask(&task1);
  scheduler.addTask(&taks2);
  scheduler.addTask(&task3);
  scheduler.begin(millis);
  //   scheduler.begin();
  Serial.println(F("Setup Done"));
}

void loop()
{
//  Serial.println(F("<---------Loop Start------------------->"));
  scheduler.run();
}
