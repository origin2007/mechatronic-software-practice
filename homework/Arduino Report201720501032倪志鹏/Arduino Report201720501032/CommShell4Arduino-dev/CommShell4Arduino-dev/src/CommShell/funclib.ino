#include "funclib.h"


FuncItem funlib[100];
int pSize=0;

void initFunLib()
{
  funlib[0].cmd = "1";
  funlib[0].func = func0;
  funlib[1].cmd = "1";
  funlib[1].func = func1;
  pSize = 2;
}

void func0( char* res)
{
  if(*res==*(funlib[0].cmd))
  {
   // strcpy(res,*res);
    strcpy(res, "1");
   // strcpy(res,funlib[0].cmd);
  }
  else
  {
    strcpy(res, "0");
   // strcpy(res, funlib[0].cmd); 
  }
}
void func1( char* res)
{
  if(*res==*(funlib[1].cmd))
  {
   // strcpy(res,*res);
    strcpy(res, "1");
   // strcpy(res,funlib[1].cmd);
  }
  else
  {
    strcpy(res, "0");
   // strcpy(res, funlib[1].cmd); 
  }
}


