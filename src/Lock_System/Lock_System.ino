// include the library code:
#include <AddicoreRFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>


//Maximum length of the array
#define MAX_LEN 16

/*
 16x2 LCD display. 
 
  The circuit:

  LCD 
  ---------------------------------------------------
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO to potentiometer 



  RFID RC522
  ---------------------------------------------------
  * RFID SDA    Digital 10
  * RFID SCK    Digital 13
  * RFID MOSI   Digital 11
  * RFID MISO   Digital 12
  * RFID IRQ    -- unconnected --
  * RFID GND    Gnd
  * RFID RST    Digital 5
  * RFID 3.3V   3.3v
 */



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module
const int chipSelectPin = 10;


void setup() {
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // start the SPI library:
  SPI.begin();

  pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin  
  digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader

  myRFID.AddicoreRFID_Init(); 
  
  // Print a message to the LCD.
  lcd.print("LCD Test !");
  lcd.setCursor(0, 1);
  lcd.print("RFID Lock Sys");
}

void loop() {
  unsigned char str[MAX_LEN];
  unsigned char status;
  
  status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);

  if (status == MI_OK)
  {
      lcd.setCursor(0, 0);
      lcd.print("Tag detected");
      delay(2000);   
  }
  else
  {
      lcd.setCursor(0, 0);
      lcd.print("No Tag");
      delay(2000);   
  }
}
