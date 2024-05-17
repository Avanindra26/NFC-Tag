# NFC-Tag
NFC Module V3
NFC Data Management on STM32/Arduino  Platform: Reading/Writing and Encryption
Implementation

• Implemented data reading and writing functionalities for NFC cards/tags using STM32
microcontroller and NFC module v3, leveraging the SPI protocol to ensure efficient and reliable
communication between the devices.

• Executed data encryption techniques within the NFC application, enhancing security measures and
safeguarding sensitive information during communication processes

1- NFC data writing using I2C protocol
1.1 Circuit Connection 
![NFC TASK 1 Circuit](https://github.com/Avanindra26/NFC-Tag/assets/30585056/a7265651-838a-4107-86f8-2be109740073)

**Algorithm**
Algorithm for Reading NFC Card Data:
A. Setup Phase:
• Add Adafruit PN532 library in Arduino IDE.
• Initialize the NFC module using SPI pins.
• Initialize serial communication with a baud rate of 115200.
• Print ”Searching for PN532...” to the serial monitor.
• Check if the PN532 board is found. If not found, print an error message and halt the program.
• Print the chip version and firmware version to the serial monitor.\

B. Loop Phase:
• Read the passive target ID of the NFC card using PN532 MIFARE protocol.
• Print the UID length and UID value to the serial monitor.
• Check if the card is a Mifare Classic card (4-byte UID). If it is a Mifare Classic card: Iterate over all 16 sectors (each having 4 blocks). Authenticate each sector using the universal key.
• If authentication is successful, write data to each block in the sector. Print the block number and the data and write the message from it to the serial monitor.
• If authentication fails or reading data fails, print an error message to the serial monitor.
• If it is not a Mifare Classic card, print an error message to the serial monitor.
• After processing all sectors, prompt the user to send a character to run the program again. Flush the serial buffer.Wait for the user to send a character.Clear the serial buffer. 

This algorithm provides step-by-step instructions for setting up and reading data from an NFC card using the PN532 module and Arduino. It ensures proper initialization, card detection, authentication, and data reading, along with error handling and user interaction.
