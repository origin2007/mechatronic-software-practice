/*
Put Declarations here. 
*/
#include "funclib.h"
#include <TaskScheduler.h>

void t0Callback();
void t1Callback();


Task t0(5000,100,&t0Callback);
Task t1(1000,200,&t1Callback);


Scheduler runner;
void t0Callback()
{
  Serial.print("t0:");
  Serial.println(millis());
}
void t1Callback()
{
  Serial.print("t1:");
  Serial.println(millis());
}

#define SIZEOFBUF 64
#define S_INI 0 /*State of initialized*/
#define S_REC 1 /*State of recieving*/
#define S_END 2 /*State of ending*/
#define S_ERR 3 /*State of error*/

char buf[64];//定义能容纳64个元素的字符数组
char retmsg[64];
int idx_p = 0;
int state;
int LEDPin=13;
const char WRONGPARAM[] = "Param Wrong.";
const char WRONGCMD[] = "Command Wrong.";

extern FuncItem funlib[];
extern int pSize;

void setup()
{
  Serial.begin(9600);
  runner.init();
  runner.addTask(t0);
  runner.addTask(t1);
  //t0.enable();
  
  state = S_INI; //initial state
  doInitial();
  pinMode(LEDPin,OUTPUT);
  Serial.println("Hello, Arduino ComShell V0.1");
}

void loop()
{
  recieveCmd();
  runner.execute();
  //processCmd();
}

void doInitial()
{
  idx_p = 0;
  buf[idx_p] = '\0';
  initFunLib();
}

void recieveCmd()
{
  if(Serial.available() > 0) //recieve no data from the serial port
  {
    char c = Serial.read();
    if(c == '\n'){ //recieve  the '\n' char from the serial port
      if(state == S_INI) return;
      if(state == S_REC){
        state = S_END; 
        doEnding();
        state = S_INI;
        doInitial();
        return;
      }
      if(state == S_ERR){
        state = S_INI;
        doInitial();
        return;
      }
    }
    else{//recieve char that is not '\n'
      if(state == S_INI || state == S_REC) {
        state =S_REC;
        if(doRecieve(c) != 0){
          state = S_ERR;
          doError();
        }
        return;
      }
    }
  }
}

int doRecieve(char c)
{
  buf[idx_p] = c;
  idx_p ++;
  if(idx_p>=SIZEOFBUF)   return 1; //error
  buf[idx_p] = '\0';
  return 0; //OK
}

void doEnding()
{
  //Serial.println(buf);
  processCmd();
}
 
void doError()
{
  Serial.println("Buffer is full.");
}

void processCmd()
{
    char delims[] = " ";
    char *Cmd = NULL;
    Cmd = strtok( buf, delims );//开头为命令 
    char *params[10];
    if(Cmd == NULL ) 
    {
        Cmd = buf;
    }
    else
    { 
      params[0]=Cmd;
      int i=1;
      while((params[i] = strtok(NULL, delims)) != NULL)// 命令不断空格分开读取
      {
        i++;
        if(i==10) break;
      }
    }
   /*digitalRead*/
  String tmpS;
  tmpS = "digitalRead";
  char* param;
  char* param2;

  //digitalRead 4 4 4 4 4 4 4 4 4 4 7
  if(tmpS.equals(Cmd)){
      param = strtok(NULL, delims);//第一个空格后字符串
      if(!checkIntParam(param)) return;
      //Serial.println(atoi(param));
      if(digitalRead(atoi(param) )== HIGH)
      {
        Serial.println("HIGH");
      }
      else
      {
        Serial.println("LOW");
      }
     return; 
  }
  /*digitalWrite*/
  tmpS = "digitalWrite"; //digitalRead 8 8 8 8 8 8 8 8 8 8 
  if(tmpS.equals(Cmd)){
      param = strtok(NULL, delims);
      if(!checkIntParam(param)) return;
      param2 = strtok(NULL, delims);
      if(!checkParam(param2)) return;
      //Serial.println(atoi(param));
     if(atoi(param2) == 0){
       digitalWrite(atoi(param), LOW);
     }  else{
       digitalWrite(atoi(param), HIGH);
     }
     Serial.println("OK");
     return;
  }
  //Cmd是输入指令的第一个
  
  for(int i=0; i<pSize; i++) {
    strcpy(retmsg, "");
    //if(strcmp((const char*)(funlib[i].cmd), params[i]) == 0)
    //{ //对应位置
        strcpy(retmsg, params[i]);
        //Serial.println(retmsg);
        funlib[i].func( retmsg);//retmsg与strcpy(res, "0 OK OK")中res一样
        //Serial.println(retmsg);
        if (atoi(retmsg) == 1)  //为位置决定何种操作
        {
          //Serial.println(i);
          switch(i){  //i是命令位置决定哪一个任务被操作
            case 0:
            //runner.addTask(t0);
            t0.enable(); Serial.println("task0");break;
            case 1:
            //runner.addTask(t1);
            t1.enable() ;Serial.println("task1");break;
            }
         
         // runner.addTask(task[0]);
         // task[0].enable();
        }
        else
        {
          //taskname = "t"+i; 
          //taskname.disable();
         // runner.deleteTask(taskname);
          switch(i){
            case 0:
            t0.disable();
            //runner.deleteTask(t0);
            break;
            case 1:
            t1.disable();
            //runner.deleteTask(t1);
            break;
            default:
            break;
            }
        }
        //Serial.println(retmsg);
        //retmsg = {0};
        //return;
      //}
  }
  
  /*put this at the end*/
  Serial.println(WRONGCMD);
  return;
}

boolean checkParam(char* param)
{
  if(param == NULL){
    Serial.println(WRONGPARAM);
    return false;
  }
  return true;
}

boolean checkIntParam(char* param)
{
  if(atoi(param) == 0){
    Serial.println(WRONGPARAM);
    return false;
  }
  return true;
}


