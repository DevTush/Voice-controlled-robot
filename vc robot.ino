#include<SoftwareSerial.h>
#define IN1 8
#define IN2 9
#define IN3 6
#define IN4 7

const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

const float stepcount = 20.00; // 20 Slots in disk, change if different


volatile int counter_A = 0;
volatile int counter_B = 0;

int enA = 10;
int enB = 5;

SoftwareSerial myserial(2,3);
String voice;
void setup() {
Serial.begin(9600);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
myserial.begin(9600);

}
// put your setup code here, to run once:

void loop() {
// put your main code here, to run repeatedly:
while(myserial.available()>0)
{
char c=myserial.read();
voice+=c;
}
if(voice.length()>0)
{
Serial.println(voice);
}

char x=' ';
int b=voice.indexOf(x);
Serial.println(b);
String side=voice.substring(b+1);
Serial.println(side);
if(side=="forward")
{
String dist=voice.substring(0,b);
int distance=dist.toInt();
Serial.println(distance);
forward(Steps(distance),255);
delay(5000);
}
if(side=="reverse")
{
String dist=voice.substring(0,b);
int distance=dist.toInt();
Serial.println(distance);
reverse(Steps(distance),255);
delay(5000);
}
if(side=="left")
{
String dist=voice.substring(0,b);
int distance=dist.toInt();
Serial.println(distance);
left(Steps(distance),255);
delay(5000);
}
if(side=="right")
{
String dist=voice.substring(0,b);
int distance=dist.toInt();
Serial.println(distance);
right(Steps(distance),255);
delay(5000);
}
else if(voice=="stop")
{
stoprobot();
}
}


void rotate_countA()
{
counter_A++; // increment Motor A counter value
}

// Motor B pulse count ISR
void rotate_countB()
{
counter_B++; // increment Motor B counter value
}

// Function to convert from centimeters to steps
int Steps(float cm) {

int result; // Final calculation result
float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
float cm_step = circumference / stepcount; // CM per Step

float f_result = cm / cm_step; // Calculate result as a float
result = (int) f_result; // Convert to an integer (note this is NOT rounded)

return result; // End and return result

}


void forward(int steps, int mspeed)
{
counter_A = 0; // reset counter A to zero
counter_B = 0; // reset counter B to zero

digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);

// Go forward until step value is reached
while (steps > counter_A && steps > counter_B) {

if (steps > counter_A) {
analogWrite(enA, mspeed);
} else {
analogWrite(enA, 0);
}
if (steps > counter_B) {
analogWrite(enB, mspeed);
} else {
analogWrite(enB, 0);
}
}

// Stop when done
analogWrite(enA, 0);
analogWrite(enB, 0);
counter_A = 0; // reset counter A to zero
counter_B = 0; // reset counter B to zero


}
void reverse(int steps, int mspeed)
{
counter_A = 0;
counter_B = 0;


digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);

// Go in reverse until step value is reached
while (steps > counter_A && steps > counter_B) {

if (steps > counter_A) {
analogWrite(enA, mspeed);
} else {
analogWrite(enA, 0);
}
if (steps > counter_B) {
analogWrite(enB, mspeed);
} else {
analogWrite(enB, 0);
}
}

// Stop when done
analogWrite(enA, 0);
analogWrite(enB, 0);
counter_A = 0; // reset counter A to zero
counter_B = 0; // reset counter B to zero


}
void left(int steps, int mspeed)
{
counter_A = 0;
counter_B = 0;

digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);

// Go until step value is reached
while (steps > counter_A && steps > counter_B) {

if (steps > counter_A) {
analogWrite(enA, mspeed);
} else {
analogWrite(enA, 0);
}
if (steps > counter_B) {
analogWrite(enB, mspeed);
} else {
analogWrite(enB, 0);
}
}

// Stop when done
analogWrite(enA, 0);
analogWrite(enB, 0);
counter_A = 0; // reset counter A to zero
counter_B = 0; // reset counter B to zero


}
void right(int steps, int mspeed)
{

counter_A = 0;
counter_B = 0;

digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);

// Go until step value is reached
while (steps > counter_A && steps > counter_B) {

if (steps > counter_A) {
analogWrite(enA, mspeed);
} else {
analogWrite(enA, 0);
}
if (steps > counter_B) {
analogWrite(enB, mspeed);
} else {
analogWrite(enB, 0);
}
}

// Stop when done
analogWrite(enA, 0);
analogWrite(enB, 0);
counter_A = 0; // reset counter A to zero
counter_B = 0; // reset counter B to zero

}
void stoprobot()
{
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
}
