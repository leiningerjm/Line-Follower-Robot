#include <AFMotor.h>
#include <Wire.h>

AF_DCMotor leftMotor(1, MOTOR12_1KHZ ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor rightMotor(2, MOTOR12_1KHZ ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  
unsigned char t;
unsigned char data[16];
unsigned char flag = 4;
#define DEBUG 1


void setup()
{
Wire.begin();
t = 0;
delay(1500);
set_motors(0,0);
}
  
void loop()
{
  
  //read the value of the linefollwing sensor
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }
  if ((data[0] < 50) && (data[14] < 50))                //When the car leaves the ground, stop working
    flag = 4;
  else if (data[0] < 110)                            
    flag = 1;
  else if (data[2] < 110)                          
    flag = 1;
  else if (data[4] < 110)                       
    flag = 1;
  else if ((data[6] < 110) || (data[8] < 110)) 
    flag = 4;
  else if (data[10] < 110)                
    flag = 7;
  else if (data[12] < 110)             
    flag = 7;
  else if (data[14] < 110)         
    flag = 7;
  else                         
    flag = 4;

  switch (flag)  
  {
    case 0: set_motors(0,0);     break;
    case 1: set_motors(0,200);   break;
    case 2: set_motors(175,255);  break;
    case 3: set_motors(255,255);  break;
    case 4: set_motors(200,200);     break;
    case 5: set_motors(255,200); break;
    case 6: set_motors(255,175); break;
    case 7: set_motors(200,0);  break;
    case 8: set_motors(0,0);   break;
    
  }
  
 Serial.begin(9600);
Serial.print("data[0]:");
  Serial.println(data[0]);
  Serial.print("data[2]:");
  Serial.println(data[2]);
  Serial.print("data[4]:");
  Serial.println(data[4]);
  Serial.print("data[6]:");
  Serial.println(data[6]);
  Serial.print("data[8]:");
  Serial.println(data[8]);
  Serial.print("data[10]:");
  Serial.println(data[10]);
  Serial.print("data[12]:");
  Serial.println(data[12]);
  Serial.print("data[14]:");
  Serial.println(data[14]);
  //delay(1000);
  
}
  
void set_motors(int leftSpeed, int rightSpeed)
{ 
leftMotor.setSpeed(leftSpeed); 
rightMotor.setSpeed(rightSpeed);
leftMotor.run(FORWARD); 
rightMotor.run(BACKWARD);
}
