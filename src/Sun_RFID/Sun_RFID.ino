/**********************************************************************************
                                RFID LOCK SYSTEM
***********************************************************************************

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
    
    Button      Digital 2
    Relay       Digital 9
    
***********************************************************************************/


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


const int relay_enable_pin = 9 ;
const int button = 2 ;

boolean relay_on = false ;






void setup()
{
    Serial.begin(9600);
    
    LCD.begin(16, 2);
    LCD.print("EEPROM DATA:");
    
    pinMode(relay_enable_pin,OUTPUT);
    digitalWrite(relay_enable_pin, LOW);
    
}







void loop()
{
    uchar status;
    uchar *str;    
    int reader_id = 1 ;
    int button_state = digitalRead(button);
    
    
    
    // Button control 
    //---------------------------------------------
    if( button_state == HIGH )
    {
        //prev_button_state = HIGH ;
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Button Pressed !!!");
        
        //digitalWrite(relay_enable_pin, !digitalRead(relay_enable_pin) );
        relay_on = !relay_on ;
        
        delay(100);        
    }
    
    
    
    // RFID Read 
    //---------------------------------------------    
    str = rfid_read(reader_id,status);                      // Read rfid tag from reader_id reader 
    if(status != MI_OK)
    {
        for(int i = 0 ; i < 4 ; i++ )                       // If status not correct str = zeros 
            str[i]=0;        
    }
    else
        relay_on = !relay_on ;
    
    
    
    
    
    // Print Results - Tag's id 
    //---------------------------------------------
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(String(str[0]) + "," + String(str[1]) + "," + String(str[2]) + "," + String(str[3])  );
    Serial.print( String(str[0]) + "," + String(str[1]) + "," + String(str[2]) + "," + String(str[3]) + "\n");
    
    

    
    // Relay Control
    //---------------------------------------------
    if(relay_on)
        digitalWrite(relay_enable_pin, HIGH);
    else
        digitalWrite(relay_enable_pin, LOW);
    
    
    
    
    delay(300);
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
    rfid.init();
    
    
    status = rfid.request(PICC_REQIDL, str);
    status = rfid.anticoll(str);

    
    return str;
}











