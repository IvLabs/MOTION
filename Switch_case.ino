int buttonState1,buttonState2,buttonState3,buttonState4 = 0;         

#define LED 14
#define Button1 3
#define Button2 5
#define Button3 6
#define Button4 7

unsigned int home_pose=1;
unsigned int sprint=2;
unsigned int walk=3;
unsigned int btry_level=4;

void setup() {
 Serial.begin(9600);
 pinMode(Button1,INPUT);  // put your setup code here, to run once:
 pinMode(Button2,INPUT);
 pinMode(Button3,INPUT);
 pinMode(Button4,INPUT);
 pinMode(LED, OUTPUT);

digitalWrite(LED, LOW);
// Wait until any button is pressed 
 while((buttonState1||buttonState2||buttonState3||buttonState4)==0)
  {
  buttonState1 = digitalRead(Button1);
  buttonState2 = digitalRead(Button2);
  buttonState3 = digitalRead(Button3);
  buttonState4 = digitalRead(Button4);
  }

if(buttonState1==HIGH)
{
Serial.write(home_pose);
delay(100);
digitalWrite(LED, HIGH);
}

else if(buttonState2==HIGH)
{
Serial.write(sprint);
digitalWrite(LED, HIGH);
delay(100);
}

else if(buttonState3==HIGH)
{
Serial.write(walk);
digitalWrite(LED, HIGH);
delay(100);
}

else if(buttonState4==HIGH)
{
Serial.write(btry_level);
digitalWrite(LED, HIGH);
delay(100);
}
}

void loop() {

}
