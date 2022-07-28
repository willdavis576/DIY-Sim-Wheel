/*
Ver 1.01 - 2015-07-17

This sketch reads data from Thrustmaster TX RW Ferrari 458 Italia racing wheel
(I mean, it reads button presses from a 'wheel' itself, not from a wheelbase :)
Wheel has 17 buttons and 3 parallel-to-serial shift registers inside. 
Data is dumped as 3 bytes via serial (SPI) line. From wheel to arduino.
3 bytes are 24 bits = 17 bits used for buttons (1 - released, 0 - pressed), 
7 first bits are reserved (static, may be they code wheel ID)
There are no leds/indicators on a wheel, so the data line from wheelbase to wheel
(green wire I suppose) is not used. In schematics it's connected to GND via 100k resistor.

Wheel cable pinout (PS/2 connector, also known as Mini Din 6pin Jack):
1 - Green  - not used
2 - Blue   - GND (ground)
3 - White  - MISO (master in, slave out - to read the data from slave)
4 - Orange - SS (slave select, or PL - parallel load, set it to 0 when you want to read the data)
5 - Red    - CLK (clock impulses)
6 - Black  - +VCC (+5 volts)

We only read 3 bytes of data from the wheel - because it has 3 8bit registers only
(can store and output unique 3 bytes)
We can read more bytes (4, 5 ....) but they all be 0b11111111

Arduino UNO pins -> TX RW wheel cable pins (connect to a wheel, not to the wheelbase!!!)

Arduino GND           -> TWRX Blue wire (2)
Arduino pin 12 (MISO) -> TXRW White wire (3) (data from wheel to base)
Arduino pin 7 (SS)    -> TXRW Orange wire (4) (Slave Select or Parallel Load in shift register terminology)
Arduino pin 13 (SCK)  -> TXRW Red wire (5)
Arduino VCC           -> TXRW Black wire (6)

BTW, TX RW wheelbase uses 3.3V power, not 5V like Arduino Uno.
(at the moment it doesn't matter, but if you decide to write a wheel emulator, you'll need 3.3V)

Free free to modify and use for your needs.
This sketch and the documentation above provided "AS IS" under the BSD New license.
http://opensource.org/licenses/BSD-3-Clause
(c) Taras Ivaniukovich (blog@rr-m.org) April 2015

http://rr-m.org/blog/hacking-a-thrustmaster-tx-rw-gaming-wheel-with-arduino-uno-part-1/
*/
#include <SPI.h>

const int slaveSelectPin = 7;

void setup() {
  Serial.begin(9600);
  SPCR |= _BV(CPHA);
  SPCR |= _BV(CPOL);
  SPI.begin();
  pinMode(slaveSelectPin, OUTPUT);
}

void loop() {
  // tell the wheel, that we gonna read the data now (capture shift registers state to start reading)
  digitalWrite(slaveSelectPin, LOW);
  
  // read 3 bytes and output them to Arduino Serial monitor as binaries 11000001 11111111 11111111
  // For TXRW 458 Italia wheel last 17 bits are buttons. 1 - released, 0 - pressed.
  for(int i=1; i<=3; i++) {
    printBinary(SPI.transfer(0x00));
  }
  Serial.println();
  
  // release the wheel
  digitalWrite(slaveSelectPin, HIGH);
 
 // wait 1 second, then read data from wheel again
  delay(1000);
}

// print byte as binary, zero padded if needed "127" -> "01111111"
void printBinary(byte data) {
  for(int i=7; i>0; i--) {
    if (data >> i == 0) {
      Serial.print("0");
    } else {
      break;
    }
  }
  
  Serial.print(data,BIN);
  Serial.print(" ");
}

