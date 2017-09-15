// SETUP
//-------------------------------------------------------------------------------------------------
void setup() {
  
  
    lcd.begin(16, 2);                         // set up the LCD's number of columns and rows: 
    SPI.begin();                              // start the SPI library:

    pinMode(chipSelectPin,OUTPUT);            // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin  
    digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader


    pinMode(relay_enable_pin,OUTPUT);
    digitalWrite(relay_enable_pin, LOW);

    myRFID.AddicoreRFID_Init(); 
  
  
    lcd.print("LCD Test !");                  // Print a message to the LCD.
    lcd.setCursor(0, 1);
    lcd.print("RFID Lock Sys");
}//-------------------------------------------------------------------------------------------------