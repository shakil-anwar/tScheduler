#include "tScheduler.h"


void func1()
{
  Serial.println(F("Task One Done"));
}

void func2()
{
  Serial.println(F("Task Two"));
}

void func3()
{
  Serial.println(F("Task Three"));
}
Task task1(2000, &func1);
Task taks2(3000, &func2);
Task task3(10000, &func3);

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
  scheduler.run();
}
