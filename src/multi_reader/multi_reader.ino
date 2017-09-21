//-------------------------------------------------------------------------------------------------
/* Pin layout used:
 * ----------------------------------
 *             MFRC522      Arduino
 *             Reader/PCD   Uno/101
 * Signal      Pin          Pin
 * ----------------------------------
 * RST/Reset   RST          9
 * SPI MOSI    MOSI         11
 * SPI MISO    MISO         12 
 * SPI SCK     SCK          13
 * SS_1                     10
 * SS_2                     8
 * SS_3                     7
 * BUTTON                   2
 */         
//-------------------------------------------------------------------------------------------------



#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

//
//-------------------------------------------------------------------------------------------------
const uint8_t RST_PIN = 9;

const uint8_t SS_1_PIN = 10;
const uint8_t SS_2_PIN = 8;
const uint8_t SS_3_PIN = 7;

const uint8_t button = 2;

//
//-------------------------------------------------------------------------------------------------
const uint8_t NR_OF_READERS = 3;
byte ssPins[] = {SS_1_PIN, SS_2_PIN, SS_3_PIN};

MFRC522 mfrc522[NR_OF_READERS];   



// SETUP
//-------------------------------------------------------------------------------------------------
void setup() 
{

    Serial.begin(9600);
    while (!Serial);
    
    SPI.begin();
    
    pinMode(button,INPUT);
    
    print_serial_eeprom(0);
    print_serial_eeprom(4);
    print_serial_eeprom(8);
    
    
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++)
        mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
}




// LOOP
//-------------------------------------------------------------------------------------------------
void loop() 
{
    
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    
        if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial())
        {
            byte card_id[] =    {   mfrc522[reader].uid.uidByte[0] ,
                                    mfrc522[reader].uid.uidByte[1] ,
                                    mfrc522[reader].uid.uidByte[2] ,
                                    mfrc522[reader].uid.uidByte[3] ,
                                };
                                
            print_serial_card_id( reader , card_id);
            delay(200);
            
            if( digitalRead(button) == HIGH )
            {
                Serial.print("\n> Register Card on Reeader : " + String(reader));
                eeprom_write( (unsigned int)reader << 2 , card_id );
            }
        }
    }
}





//-------------------------------------------------------------------------------------------------
void print_serial_card_id( uint8_t reader , byte *id )
{
    Serial.print("\nReader " + String(reader) + " :");
    Serial.print("\n"  + String(id[0]) + " , " + String(id[1]) );
    Serial.print(" , " + String(id[2]) + " , " + String(id[3]) );
    Serial.print("\n");
    
}




//-------------------------------------------------------------------------------------------------





// EEPROM FUNCTIONS
//-------------------------------------------------------------------------------------------------
void print_serial_eeprom( int start_address )
{
    Serial.print("\nEEPROM DATA , Address " + String(start_address) + " :\n");
    Serial.print(   String(EEPROM.read(start_address))   + " , " + 
                    String(EEPROM.read(start_address+1)) + " , " + 
                    String(EEPROM.read(start_address+2)) + " , " + 
                    String(EEPROM.read(start_address+3))
                );
    Serial.print("\n");
}



void eeprom_write(const unsigned int start_address, byte *id)
{
    for(int i = 0 ; i < 4 ; i++)
        EEPROM.write(start_address+i, id[i]);
}



void wipe_eeprom()
{
    int i = 0 ;

    for(i=0 ; i<EEPROM.length() ; i++ )
        EEPROM.write(i,0);

}

