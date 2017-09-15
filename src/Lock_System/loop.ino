// LOOP
//-------------------------------------------------------------------------------------------------
void loop() {
    unsigned char str[MAX_LEN];
    unsigned char status;
    
    int button_state = digitalRead(button);
    
    
    // Button control 
    //---------------------------------------
    if(/*prev_button_state == LOW &&*/ button_state == HIGH )
    {
        //prev_button_state = HIGH ;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button Pressed !!!");
        
        //digitalWrite(relay_enable_pin, !digitalRead(relay_enable_pin) );
        relay_on = !relay_on ;
        
        delay(200);        
    }

    
    
    // RFID read 
    //---------------------------------------
    status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);
    status = myRFID.AddicoreRFID_Anticoll(str);
    if (status == MI_OK)
    {
        // Print RFID Tag to LCD
        //---------------------------------------
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(String(str[0]) + "," + String(str[1]) + "," + String(str[2]) + "," + String(str[3])  );
        
        relay_on = !relay_on ;
        
        
        
        // Write to EEPROM
        //---------------------------------------
        EEPROM.write(0, str[0]);
        EEPROM.write(1, str[1]);
        EEPROM.write(2, str[2]);
        EEPROM.write(3, str[3]);
        
        
        
        delay(200);
        
        
    }

    
    // Relay Control
    //---------------------------------------
    if(relay_on)
        digitalWrite(relay_enable_pin, HIGH);
    else
        digitalWrite(relay_enable_pin, LOW);
    
    
    
    
    
    
}
//-------------------------------------------------------------------------------------------------