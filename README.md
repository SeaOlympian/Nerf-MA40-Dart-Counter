# Nerf-MA40-Dart-Counter
Nerf blaster visual dart counter and clip capacity detector.

Please note that this project was created as a senior project and for fun therefore I will not be able to help answer any questions or fix any problems that may arise. I also take no responsibility if you damage you blaster or injure yourself by modifying it.

---

## Parts List:
  - One Arduino compatible board of some kind (I used a Teensy 3.2. See why below)
  - Two [Hall Effect sensors](https://www.amazon.com/gp/product/B07QS6PN3B/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
  - One [I2C OLED Screen](https://www.amazon.com/gp/product/B0761LV1SD/ref=ppx_yo_dt_b_asin_title_o05_s01?ie=UTF8&psc=1)
  - One microswitch/limit switch
  
## Why did I use a Teensy 3.2?
    There are two reasons why I decided to use a Teensy 3.2
        - It's Vin accepts 3.6 to 6.0 volts. This allows it to be use directly off of the four C batteries without the need for anything else.
        - I already had one laying around.

  ![Blaster Internals Before](/Media/Blaster_Internals_(Before).png)
  ![Teensy 3.2 Wiring Diagram](/Media/Wiring_Diagram.png)
