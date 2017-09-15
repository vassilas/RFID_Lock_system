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
        
        relay_on = !relay_on ;
        
        delay(1000);
    
    }
    /*else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Tag");
        delay(500);        
    }*/
    
    if(relay_on)
        digitalWrite(relay_enable_pin, HIGH);
    else
        digitalWrite(relay_enable_pin, LOW);

}
//-------------------------------------------------------------------------------------------------