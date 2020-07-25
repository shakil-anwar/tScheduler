#include "tScheduler.h"
#include <TimerOne.h>

uint32_t milliSec = 0;
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

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timeCounter);
  scheduler.addTask(&task1);
  scheduler.addTask(&taks2);
  scheduler.addTask(&task3);
  scheduler.begin(ms);
  //   scheduler.begin();
  Serial.println(F("Setup Done"));
}

void loop()
{
//  Serial.println(F("<---------Loop Start------------------->"));
  scheduler.run();
}
void timeCounter()
{
  milliSec++;
}

uint32_t ms()
{
  return milliSec;
}

