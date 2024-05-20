#include <SPI.h>

// SPI settings
const int chipSelectPin = 10; // Chip select pin for the SPI device


// Function to write data to a specific register of the SPI device
void writeDataToSPI(uint8_t registerAddress, uint8_t data) {
    digitalWrite(chipSelectPin, LOW); // Pull the chip select pin low to select the device
    SPI.transfer(registerAddress);    // Send register address
    SPI.transfer(data);               // Send data
    digitalWrite(chipSelectPin, HIGH); // Pull the chip select pin high to deselect the device
}

// Function to read data from a specific register of the SPI device
uint8_t readDataFromSPI(uint8_t registerAddress) {
    digitalWrite(chipSelectPin, LOW); // Pull the chip select pin low to select the device
    SPI.transfer(registerAddress);    // Send register address
    uint8_t data = SPI.transfer(0x00); // Send dummy byte to read data
    digitalWrite(chipSelectPin, HIGH); // Pull the chip select pin high to deselect the device
    return data;
}


void setup() {
    // Set the chip select pin as an output
    pinMode(chipSelectPin, OUTPUT);
    digitalWrite(chipSelectPin, HIGH); // Set chip select high to start with

    // Initialize the SPI bus
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16); // Set SPI clock speed (change as needed)
    SPI.setDataMode(SPI_MODE0); // Set SPI mode (change as needed)
    SPI.setBitOrder(MSBFIRST); // Set bit order (change as needed)

    // Initialize serial communication for debugging
    Serial.begin(MONITOR_SPEED);

    // Give some time for the serial monitor to start
    while (!Serial);

    // Test writing to the SPI device
    writeDataToSPI(0x01, 0x23); // Example: writing data to register 0x01
}

void loop() {
    // Test reading from the SPI device
    uint8_t data = readDataFromSPI(0x01); // Example: reading data from register 0x01

    // Print the read data to the serial monitor
    Serial.print("Data read from SPI: ");
    Serial.print("HEX: ");
    Serial.print(data, HEX);
    Serial.print("    DEC: ");
    Serial.println(data, DEC);

    // Delay for a while before reading again
    delay(500);
}