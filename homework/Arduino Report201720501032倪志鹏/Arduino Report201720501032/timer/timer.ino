#include <MsTimer2.h>
int onoff = 0;
int t0 = 500;
void ONandOFF() { 
  onoff += 1;
  digitalWrite(13, onoff % 2);
  //delay(300);
}
void setup() {  
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  MsTimer2::set(t0, ONandOFF);
  MsTimer2::start();
}
void loop() { 
  //MsTimer2::set(500,turnOff);
  float msg;
  if (Serial.available())
  {
    //msg = 0;
    msg = Serial.parseFloat(); 
    Serial.print("输入频率：");
    Serial.println(msg);  
    t0 = 500/msg;
    MsTimer2::stop();
    MsTimer2::set(t0, ONandOFF);  //t0，设置时间
    MsTimer2::start();
  }
}

