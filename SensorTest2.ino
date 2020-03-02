#include <Wire.h>
unsigned char t;
unsigned char data[16];
unsigned char flag = 4;





void setup() {
  // put your setup code here, to run once:

  Wire.begin();
  t = 0;

}

void loop() {
  // put your main code here, to run repeatedly:

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

int min_value = 9999; // larger than in your array.
int index = -1;

  for (int i = 0; i<14; i++)
{
    if (data[i] < min_value) {
         index = i;
     
    }
}
   if ((data[0] < 50) && (data[14] < 50))                //When the car leaves the ground, stop working
    flag = 0;
  else if (index == 0)                            
    flag = 1;
  else if (index == 2)                          
    flag = 2;
  else if (index == 4)                       
    flag = 3;
  else if ((index == 6) || (index == 8)) 
    flag = 4;
  else if (index == 10)                
    flag = 5;
  else if (index == 12)             
    flag = 6;
  else if (index == 14)         
    flag = 7;
  else                         
    flag = 8;

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
  Serial.print("flag:");
  Serial.println(flag);
  delay(1000);

}
