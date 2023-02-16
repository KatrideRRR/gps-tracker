#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino D3 & D2

void setup()
{
  Serial.begin(9600);
  
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); //Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+0000000000\""); //Zeroes need to be replaced by phone number

  updateSerial();
  mySerial.print("Hello, world!!! From Sim module"); //Sms text content
  updateSerial();
  mySerial.write(26); //Operation termination
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read()); //Forward what Software Serial received to Serial Port
  }
}
