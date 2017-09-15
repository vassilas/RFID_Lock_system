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
    

    
    lcd.print("EEPROM DATA:");
    lcd.setCursor(0, 1);
    lcd.print(  String(EEPROM.read(0)) + "," + 
                String(EEPROM.read(1)) + "," + 
                String(EEPROM.read(2)) + "," + 
                String(EEPROM.read(3))          );
    
  
}//-------------------------------------------------------------------------------------------------



