
/*-------------------------------------------------------------------------------------------------
    Description :
        If a RFID tag is the correct one , then turn on a relay

---------------------------------------------------------------------------------------------------

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
-------------------------------------------------------------------------------------------------*/




#include <AddicoreRFID.h>                   // include the library code:
#include <SPI.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define MAX_LEN 16                          // Maximum length of the array


LiquidCrystal lcd(7, 6, 5, 4, 3, 8);        // initialize the library with the numbers of the interface pins
AddicoreRFID myRFID;                        // create AddicoreRFID object to control the RFID module


const int chipSelectPin = 10 ;
const int relay_enable_pin = 9 ;
const int button = 2 ;

int prev_button_state = LOW ;

boolean relay_on = false ;










