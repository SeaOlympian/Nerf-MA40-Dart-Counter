# Nerf-MA40-Dart-Counter
Nerf blaster visual dart counter and clip capacity detector.

Please note that this project was created as a senior project and for fun therefore I will not be able to help answer any questions or fix any problems that may arise. I also take no responsibility if you damage you blaster or injure yourself by modifying it.

---

## Parts List:
  - One Arduino compatible board of some kind (I used a Teensy 3.2. See why below)
  - Two [Hall Effect sensors](https://www.amazon.com/gp/product/B07QS6PN3B/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
  - One [I2C OLED Screen](https://www.amazon.com/gp/product/B0761LV1SD/ref=ppx_yo_dt_b_asin_title_o05_s01?ie=UTF8&psc=1)
  - One microswitch/limit switch
  - One Capacitor (I used a 100µF that I had laying around)
  - Micro USB to USB Type C adapter (Optional)

## Why did I use a Teensy 3.2?
There are two reasons why I decided to use a Teensy 3.2
  - It's Vin accepts 3.6 to 6.0 volts. This allows it to be use directly off of the four C batteries without the need for a voltage regulating circuit.
  - I already had one laying around.

  ![Blaster Internals Before](/Media/Blaster_Internals_(Before).png)
  Take a good look at where the pieces of the blaster are such as the trigger and magazine catch. Also take the time to figure out where you want to put the power switch and microcontroller. I wanted the power switch somewhere it could not be easily bumped and wanted to be able to update the code on my Teensy without tearning the whole blaster apart again.

  ![Teensy 3.2 Wiring Diagram](/Media/Component_Wiring_Diagram.png)
  Because of the location I wanted to put the Teensey I tried to wire everything towards the bottom of it. If you want to place it in a different location or are using a different microcontroller feel free to change the pins used.

  ![Power Wiring Diagram](/Media/Power_Wiring_Diagram.png)
  I ran into a problem after I finished everything where the fly wheels would draw too much current when a dart went through them causing the Teensy to restart. So in order to fix the problem I added a 100µF capacitor as a temporary resivoir to keep the Teensy running for those short moments.
