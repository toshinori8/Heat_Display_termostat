/*
  This sketch is based on the sdFatTftBitmap example sketch from the ILI9341_due library.

  See: http://marekburiak.github.io/ILI9341_due/
  
  Adapted by Bodmer 20th January 2017 to incorporate the JPEGDecoder library and draw
  Jpeg images that have been stored on an SD card.

  It is compatible with the Mega and Due boards, modify the defined CS, DC pins
  for the TFT and SD connections to suit your setup.

  You can generate your own Jpeg images from digital photographs by cropping and resizing
  by using commonly available picture/image editors such as Paint or IrfanView.
  The example image used by the sketch is in the extras folder in the JPEGDecoder library,
  copy the "arduino.jpg" file to the SD card.

  See: https://github.com/Bodmer/JPEGDecoder

  The Arduino IDE's built in SD library is used:

  https://www.arduino.cc/en/reference/SD
*/

//  IMPORTANT: Edit the ILI9341_due_config.h to select:
//    #define ILI9341_SPI_MODE_NORMAL  // uses SPI library
//  this sketch will not work if the Due DMA or SPI extended mode is enabled.
//  Use the hardware SPI lines MOSI, MISO and SCK to interface with both the TFT and
//  the SD card.

//====================================================================================
//  libraries
//====================================================================================

#include <SPI.h>
#include <SD.h>  // Use the Arduino IDE built-in SD library
  
#include <ILI9341_due_config.h>
#include <ILI9341_due.h>

#include <JPEGDecoder.h>  // JPEG decoder library

int CH_PD_8266 = 50; // High gdy normalna praca
int RST_ESP = 44;    // Reset PIN musi być na HIGH ponieważ nie ma podwieszenia do VCC
int VCC_lcd = 15;
//====================================================================================
//  defines
//====================================================================================

#define TFT_RST 8	// Reset for TFT
#define TFT_DC 9	// Command/Data for TFT
#define TFT_CS 10	// Chip Select for TFT

#define SD_CS 41		// Chip Select for SD card

#define TFT_BLACK 0x0000
#define TFT_WHITE 0xFFFF

//====================================================================================
//  setup
//====================================================================================
#define ILI9341_SPI_CLKDIVIDER 2
//ILI9341_due tft = ILI9341_due(TFT_CS, TFT_DC, TFT_RST);
ILI9341_due tft = ILI9341_due(38,39,40,41);
void setup()
{

  pinMode(VCC_lcd, OUTPUT);
  pinMode(CH_PD_8266, OUTPUT);
  delay(1000);
  digitalWrite(RST_ESP, HIGH);
  digitalWrite(CH_PD_8266, HIGH); // +3.3V  PIN 50 ESP TURN ON
  digitalWrite(VCC_lcd, HIGH);  
  
  Serial.begin(9600);

  // Make sure the SD card chip select is high before we initialise the TFT
//  pinMode(SD_CS, OUTPUT);
//  digitalWrite(SD_CS, LOW);

  // Initialise the TFT
  tft.begin();
  tft.fillScreen(TFT_BLACK);
    
tft.drawCircle(100, 100, 20, ILI9341_WHITE);
 

  Serial.print(F("Initialising SD card..."));

  if (!SD.begin(SD_CS )){
    Serial.println(F("failed!"));
    return;
  }
  Serial.println(F("OK!"));
}


//====================================================================================
//  loop
//====================================================================================

void loop()
{
  tft.setRotation((iliRotation)0); // Landscape orientation

  // draw Arduino logo at a random position
  drawJpeg( "arduino.jpg", random(tft.width() - 160), random(tft.height() - 128) );
 
  delay(2000);

  tft.fillScreen(random(0xFFFF));
}
