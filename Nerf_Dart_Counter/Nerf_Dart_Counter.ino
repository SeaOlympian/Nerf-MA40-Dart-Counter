#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Compass Bitmap
#define compass_height 16
#define compass_width 10
static const unsigned char PROGMEM compass_bmp[] =
{ 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x1e, 0x00, 0x3f, 0x00, 
0x3f, 0x00, 0x3f, 0x00, 0x7f, 0x80, 0x7f, 0x80, 0x7f, 0x80, 0xff, 0xc0, 0x00, 0x00, 0x1e, 0x00 };

//Dart Icon Bitmap
#define dart_height 7
#define dart_width 20
static const unsigned char PROGMEM dart_bmp[] =
{ 0x50, 0x00, 0x00, 0xd9, 0xff, 0xe0, 0x03, 0x00, 0x70, 0x03, 0x00, 0x70, 0x03, 0x00, 0x70, 0xd9, 
0xff, 0xe0, 0x50, 0x00, 0x00 };

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setRotation(1);

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

}

void loop() {
  display.clearDisplay();
  
  drawCompassBitmap();
  drawDartBitmap();
  dartCount();

}

void drawCompassBitmap(void)
{
  display.drawBitmap(
    (display.width() - compass_width) / 2,
    5, compass_bmp, compass_width, compass_height, 1);
  display.display();
}

void drawDartBitmap(void)
{
  display.drawBitmap(
    (display.width() - dart_width) / 2,
    110, dart_bmp, dart_width, dart_height, 1);
  display.display();
}

void dartCount(void) {
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text

  int dartTotal = 10;

  //Display countdown from 10 to 0
  for (int i=dartTotal; i >= 0;){
    
    if (i >= 10)
      display.setCursor(5,  60);
    else
      display.setCursor(11, 60);
    display.println(i);     //Print i to display
    Serial.println(i);
    display.display();
  }
}
