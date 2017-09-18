/*******************************************

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


#define RFID_IRQ 1
#define RFID_SCK 13
#define RFID_CS 10
#define RFID_RST 0
#define RFID_MOSI 11
#define RFID_MISO_1 12
#define RFID_MISO_2 12
#define RFID_MISO_3 12



LiquidCrystal LCD(7, 6, 5, 4, 3, 8);
RFID rfid;





void setup()
{
    Serial.begin(9600);
    
    LCD.begin(16, 2);
    LCD.print("EEPROM DATA:");
    
}


void loop()
{
    uchar status;
    uchar *str;    
    

    str = rfid_read(1,status);
    if(status != MI_OK)
    {
        for(int i = 0 ; i < 4 ; i++ )
            str[i]=0;        
        
    }
    
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(String(str[0]) + "," + String(str[1]) + "," + String(str[2]) + "," + String(str[3])  );
    
    
    delay(500);
}





uchar* rfid_read(int id, uchar &status)
{

    uchar str[4];
    int miso = RFID_MISO_1 ;
    

    switch (id) {
        case 1:
            miso = RFID_MISO_1 ;
            break;
        case 2:
            miso = RFID_MISO_2 ;
            break;
        case 3:
            miso = RFID_MISO_3 ;
            break;
        default: 
            miso = RFID_MISO_1 ;
        break;
    }    
    
    
    
    
    rfid.begin(RFID_IRQ,RFID_SCK,RFID_MOSI,miso,RFID_CS,RFID_RST);
    rfid.init(); //initialize the RFID
    
    
    status = rfid.request(PICC_REQIDL, str);
    status = rfid.anticoll(str);

    
    return str;
}











