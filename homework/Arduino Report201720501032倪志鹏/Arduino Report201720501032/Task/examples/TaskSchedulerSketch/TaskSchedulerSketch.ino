#include "Task.h"  // include this file to use this library
void setup()
{
    Serial.begin(115200);
    Sch.init();  // Initialize task scheduler
    /*
     * use Sch.addTask(task, start_time, period, priority) to add tasks
     * task - tasks to be scheduled
     * start_time - when the task starts (ms)
     * period - repeat period of the task (ms)
     * priority - 1: mormal priority, 0: high priority
     */
    Sch.addTask(task1,0,1000,1);  //从第 0 毫秒开始 LED，每隔 1s, 
    Sch.addTask(task2,20,500,1);  //从第 20 毫秒开始 LED，每隔 0.5s, 

    Sch.start();  // Start the task scheduler
}
void loop()
{  
    Sch.dispatchTasks();
}
// Put task to be scheduled below
void task1()
{ 
   Serial.print("t1:");
   Serial.println(millis());
}
int n = 0;
void task2()
{
   n++;
   if (n == 8)
   {
      Sch.deleteTask(0);
      Serial.println("delete task1");
   }
    Serial.print("t2:");
    Serial.println(millis());
}
