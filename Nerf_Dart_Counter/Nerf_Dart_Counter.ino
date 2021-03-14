#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <JC_Button.h>

//Set to true to debug.
bool Debug = false;

int Hall_Pin_1 = 14;
int Hall_Pin_2 = 15;

//Uses JC_Button to create a button with debouncing.
Button Switch(13);

//Maximum number of darts in mag.
int dartMax;
//Current number of darts in mag.
int dartCurrent;
//State of the mag, 1 if empty, 0 if there are darts.
int magEmpty = 0;

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

  pinMode(Hall_Pin_1, INPUT_PULLUP);
  pinMode(Hall_Pin_2, INPUT_PULLUP);

  //Creates instance of button with the name Switch.
  Switch.begin();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  //Rotates the display 90 degrees.
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
  
  magCheck();     //Selects the magazine size.
  drawCompassBitmap();
  drawDartBitmap();
  trigger();    //Decrements the current dart count.
  dartCount();    //Displays the current dart count.

  //Prints out hall effect sensor readings and dart maximum if debug is enabled.
  if (Debug){   
    Serial.print("Sensor One: ");
    Serial.println(digitalRead(Hall_Pin_1));

    Serial.print("Sensor Two: ");
    Serial.println(digitalRead(Hall_Pin_2));

    Serial.print("Dart Total: ");
    Serial.println(dartMax);
    };
    
    display.display();
}

//----------FUNCTIONS----------

void drawCompassBitmap(void)
{
  display.drawBitmap(
    (display.width() - compass_width) / 2,
    5, compass_bmp, compass_width, compass_height, 1);
  //display.display();
}

//--------------------

void drawDartBitmap(void)
{
  display.drawBitmap(
    (display.width() - dart_width) / 2,
    110, dart_bmp, dart_width, dart_height, 1);
  //display.display();
}

//--------------------

void magCheck(){
  //Checks states of hall effect sensors and determines correct mag size.
  if (digitalRead(Hall_Pin_1) == 0 && digitalRead(Hall_Pin_2) == 1)
    dartMax = 10;
  else if (digitalRead(Hall_Pin_1) == 1 && digitalRead(Hall_Pin_2) == 0)
    dartMax = 6;
  else if (digitalRead(Hall_Pin_1) == 1 && digitalRead(Hall_Pin_2) == 1){
    dartMax = 0;
    magEmpty = 1;
  }

  //Checks to see of the current dart count should be reset.
  if (magEmpty == 1 && dartMax !=0){
    dartCurrent = dartMax;
    magEmpty = 0;
  }
}

//--------------------

void trigger(){
  //Recordes the state of the switch.
  Switch.read();

  if (Switch.wasReleased() && dartCurrent != 0)
    dartCurrent--;
}

//--------------------

void dartCount() {
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text

  //Display countdown
  if (dartCurrent >= 10)
    display.setCursor(5,  60);      //Selects cursor position based on number of characters.
  else
      display.setCursor(11, 60);
  if (dartMax != 0)
    display.println(dartCurrent);     //Prints current number of darts to display if there is a mag.
  else{
    display.setCursor(5,  60);
    display.println("--");
  }
  //display.display();
}
