 #include <Wire.h>
 #include <SPI.h>
 #include <Adafruit_PN532.h>
 // using spi pins
 #define PN532_SCK (13)
 #define PN532_MOSI (11)
 #define PN532_SS (10)
 #define PN532_MISO (12)
 #define MI_OK
 Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
 void setup(void) 
  {
              Serial.begin(115200);
          while (!Serial) delay(10);
               Serial.println("Searching for PN532...");
               nfc.begin();
               uint32_t versiondata = nfc.getFirmwareVersion();
                 if (! versiondata) 
                   {
                     Serial.print("Didn’t find PN53x board");
                     while (1); // halt
                   }
                     Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
                     Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
                     Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
                     Serial.println("Waiting for an NFC Card ...");
 }
    
    
          void loop(void) 
  {
           uint8_t success;
            // Flag to check if there was an error with the PN532
           uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; 
          // Buffer to store the returned UID
          uint8_t uidLength;
         // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
          uint8_t i;

           bool authenticated = false;
           // Flag to indicate if the sector is authenticated
           uint8_t data[16];
           // Array to store block data during reads

           uint8_t keyuniversal[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
           success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success)
   {
      Serial.println("Found an ISO14443A card");
      Serial.print(" UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
      Serial.print(" UID Value: ");
      nfc.PrintHex(uid, uidLength);
      Serial.println("");

      if (uidLength == 4)
      {
        Serial.println("This is a Mifare Classic card (4 byte UID)");
          // Now we try to go through all 16 sectors (each having 4 blocks)
          // authenticating each sector, and then dumping the blocks
          for (i = 0; i < 64; i++)
           {
              if (nfc.mifareclassic_IsFirstBlock(i)) authenticated = false;
              if (!authenticated)
             {
                  Serial.print("------------------------Sector");
                  Serial.print(i/4,DEC);
                  Serial.println("-------------------------");
                    if (i == 0)
                    {
                      success = nfc.mifareclassic_AuthenticateBlock (uid,uidLength, i, 1, keyuniversal);
                    }
                   else
                    {
                      success = nfc.mifareclassic_AuthenticateBlock (uid,uidLength, i, 1, keyuniversal);
                    }
                   if (success)
                    {
                       authenticated = true;
                    }
                   else
                    {
                     Serial.println("Authentication error");
                    }
                    if (!authenticated)
                    {
                      Serial.print("Block ");Serial.print(i, DEC);Serial.println(" unable to authenticate");
                    }
                   else
                   {
                      success = nfc.mifareclassic_ReadDataBlock(i, data);
                   }
                   if (success)
                   {
                       // Read successful
                      Serial.print("Block ");Serial.print(i, DEC);
                    if (i < 10)
                    {
                     Serial.print(" ");
                    }
                    else
                    {
                      Serial.print(" ");
                    }
                       // Dump the raw data
                       nfc.PrintHexChar(data, 16);}
                    else
                    {
                       // Oops ... something happened
                        Serial.print("Block ");Serial.print(i, DEC);
                        Serial.println(" unable to read this block");
                    }
               }
            }
      }
               else
               {
                  Serial.println("this doesn't seem to be a Mifare Classic card!");
               }
    }
                  Serial.println("\n\nSend a character to run the mem dumper again!");
                   Serial.flush();
                        while (!Serial.available());
                        while (Serial.available()) 
                        {
                              Serial.read();
                        }
                              Serial.flush();
 }
 