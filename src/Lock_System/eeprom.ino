

void wipe_eeprom()
{
    int i = 0 ;

    for(i=0 ; i<EEPROM.length() ; i++ )
        EEPROM.write(i,0);

}