/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void move_vectorscope(int x, int y)
{
  
  const u8 move_line[] = {0,
                          0xa8, 1, 0xd3, (y & 63), 0x40 + (x & 63)
                         };
  Wire.beginTransmission(0x3C);              // START I2C COMMUNICATION WITH OLED (0x3c=OLED ADDRESS)
 // Wire.write(0x80);                          // WRITE I2C COMMAND WORD TO OLED
 int i;
 for(i=0;i<sizeof(move_line);i++)
  Wire.write(move_line[i]);                          // SEND I2C VALUE TO OLED (0xA7=INVERSE DISPLAY)
  Wire.endTransmission();                    // STOP I2C COMMUNICATION
  
}


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  display.clearDisplay();
  display.drawLine(0, 0, 127,63, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line

  
  float counter=0;
  
  
  
  for(;;)
  {
     move_vectorscope(sin(counter)*27+31,cos(counter*1.01)*27+31);
     counter+=0.01;

  }
  
  
}

void loop() {
}
