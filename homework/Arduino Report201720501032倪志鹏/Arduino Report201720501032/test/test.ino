String msg="";
int LEDpin=13;
void setup() {
  Serial.begin(9600);
  pinMode(LEDpin,OUTPUT);
}
void loop() {
 //while(Serial.available()>0)
 {
 //   msg +=char(Serial.read());
   // delay(2);
 }
 //if(msg.length()==6&&msg[4]==48)
 {
    digitalWrite(LEDpin,HIGH);
    delay(500);
    digitalWrite(LEDpin,LOW);
    delay(500);
 }
  //msg="";
}
