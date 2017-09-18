/*******************************************

* RFID   SunFounder Uno
* VCC     3.3V
* RST     2
* GND     GND
* MISO    3
* MOSI    4
* SCK     5
* NSS     6
* IRQ     7







    LCD 
    ---------------------------------------------------
    LCD RS pin to digital pin 7
    LCD Enable pin to digital pin 6
    LCD D4 pin to digital pin 5
    LCD D5 pin to digital pin 4
    LCD D6 pin to digital pin 3
    LCD D7 pin to digital pin 8
    LCD R/W pin to ground
    10K potentiometer:
    ends to +5V and ground
    wiper to LCD VO to potentiometer 



    RFID RC522
    ---------------------------------------------------
    RFID SDA    Digital 10
    RFID SCK    Digital 13
    RFID MOSI   Digital 11
    RFID MISO   Digital 12
    RFID IRQ    NC              (-- Not Connected --)
    RFID GND    Gnd
    RFID RST    Digital 5
    RFID 3.3V   3.3v
    
****************************************/


#include "rfid.h"
#include <LiquidCrystal.h>
#include <Wire.h>


LiquidCrystal LCD(7, 6, 5, 4, 3, 8);
RFID rfid;




#define relayPin 8 //relay module attach to pin8




void setup()
{
    Serial.begin(9600);
    
    LCD.begin(16, 2);
    LCD.print("EEPROM DATA:");
    
    rfid.begin(1,13,11,12,10,0); //IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN
    delay(100);
    rfid.init(); //initialize the RFID
    
}


void loop()
{
    uchar status;
    uchar str[MAX_LEN];    
    
    
    status = rfid.request(PICC_REQIDL, str);
    
    status = rfid.anticoll(str);
    if (status == MI_OK)
    {
        //Serial.print("The card's number is: ");

        
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print(String(str[0]) + "," + String(str[1]) + "," + String(str[2]) + "," + String(str[3])  );
    }
}