int sinputPin = 10; /*Change according to the hardware configure*/
int soutputPin = 8;/*Change according to the hardware configure*/
int buzzPin = 7;/*Change according to the hardware configure*/
int wait;

void setup()
{
  //set the IO working mode
  pinMode(sinputPin, INPUT);
  pinMode(soutputPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  //Setup the serial port
  Serial.begin(9600);
}

void loop()
{
  //the next 5 lines are used to generate a pulse 
  //to trig the ultrasonic ranging unit 
  digitalWrite(soutputPin, LOW);
  delay(100);
  digitalWrite(soutputPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(soutputPin, LOW);
  //get response from the ranging unit
  unsigned int distance = pulseIn(sinputPin, HIGH);
  distance = distance/58; //in cm
  if(distance < 20){
    tone(buzzPin, 2000, 100);
    wait = 200;
  }
  else if(distance > 100)
  {
   tone(buzzPin, 800, 100);
    wait = 2000;
  }
  else{
    tone(buzzPin, 1000, 100);
    wait = 1000;
  }
  //display the results to the serial monitor 
  Serial.print("[");
  Serial.print(millis());
  Serial.print("]");
  Serial.print(" ");
  Serial.print(distance); 
  Serial.println("cm");
  delay(wait);
}

