
/*
    Description :
        If a RFID tag is the correct one , then turn on a relay



    1) Arduino UNO
    2) 16x2 LCD display. 
    3) RFID RC522 
 
    The circuit:

    LCD 
    ---------------------------------------------------
    LCD RS pin to digital pin 7
    LCD Enable pin to digital pin 6
    LCD D4 pin to digital pin 5
    LCD D5 pin to digital pin 4
    LCD D6 pin to digital pin 3
    LCD D7 pin to digital pin 2
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
 */


//-------------------------------------------------------------------------------------------------
// include the library code:
#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>


//Maximum length of the array
#define MAX_LEN 16
//-------------------------------------------------------------------------------------------------





LiquidCrystal lcd(7, 6, 5, 4, 3, 2);        // initialize the library with the numbers of the interface pins
AddicoreRFID myRFID;                        // create AddicoreRFID object to control the RFID module





// PINS
const int chipSelectPin = 10;





// SETUP
//-------------------------------------------------------------------------------------------------
void setup() {
  
  
    lcd.begin(16, 2);                         // set up the LCD's number of columns and rows: 
    SPI.begin();                              // start the SPI library:

    pinMode(chipSelectPin,OUTPUT);            // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin  
    digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader

    myRFID.AddicoreRFID_Init(); 
  
  
    lcd.print("LCD Test !");                  // Print a message to the LCD.
    lcd.setCursor(0, 1);
    lcd.print("RFID Lock Sys");
}
//-------------------------------------------------------------------------------------------------





// LOOP
//-------------------------------------------------------------------------------------------------
void loop() {
    unsigned char str[MAX_LEN];
    unsigned char status;
  
    status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);

    lcd.clear();
    lcd.setCursor(0, 0);
    
    /*
    if (status == MI_OK)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tag detected");
        delay(500);   
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Tag");
        delay(500);   
    }
    */

    status = myRFID.AddicoreRFID_Anticoll(str);
    if (status == MI_OK)
    {
        // Print RFID Tag to LCD
        //---------------------------------------
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(String(str[0]) + "," + String(str[1]) + "," + String(str[2]) + "," + String(str[3])  );
        delay(500);

    }
    /*else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Tag");
        delay(500);        
    }*/
    

}
//-------------------------------------------------------------------------------------------------
