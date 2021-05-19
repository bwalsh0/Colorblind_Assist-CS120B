# Colorblind_Assist-CS120B

### Description
The Colorblind Assistant is intended to help people with difficulty in recognizing colors.
When the sensor is pointed at an object, the device will sound a specific tone and display
that color’s RGB hex code. A color at the red-black end of the light spectrum will play a
lower pitch, and a color on the blue-black end will play a higher pitch. This provides the
user with a cumulative awareness of color on a complex object based on the
temperament of the played tones.


### Usage
The Colorblind Assistant uses an RGB Sensor to interpret the light as data, and an
ATmega1284 to convert the data as sound and RGB hex. An LED at the front of the
sensor will illuminate the object for accuracy, and a proximity sensor will ensure that the
object is close enough for a proper reading. The device is paired with an LCD to provide
an additional method of interpreting the observed color with precision, as well as error
and status output.


### Hardware Components
* ATmega1284
* 2004A 20x4 LCD
* TCS34725 RGB Color Sensor
* HC-SR04 Proximity Sensor

---
### References
* ATmega1284 Datasheet: http://ww1.microchip.com/downloads/en/devicedoc/atmel-42718-atmega1284_datasheet.pdf
* TCS34725 Color Sensor Datasheet: https://cdn-shop.adafruit.com/datasheets/TCS34725.pdf
* HC-SR04 Proximity Sensor Datasheet: https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
* Peter Fleury’s i2C Library: http://homepage.hispeed.ch/peterfleury/doxygen/avr-gcc-libraries/group__pfleury__ic2master.html
* Adafruit’s TCS34725 C++ Library: https://github.com/adafruit/Adafruit_TCS34725
* JRodrigoTech’s HC-SR04 C++ Library: https://github.com/JRodrigoTech/Ultrasonic-HC-SR04
* NASA’s Blog on Color & Sound: https://helios.gsfc.nasa.gov/qa_gp_ls.html


