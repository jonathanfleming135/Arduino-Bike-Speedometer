# Arduino-Bike-Speedometer
LCD Speedometer created for my bike

## Description
Using an Arduino Nano, an LCD screen, Hall effect sensor, magnet, and crafty electrical tape and zipties - I created a little speedometer for my bike. Essentially, I just attached the magnet and Hall effect sensor to my tire, and every time my tire rotated, the magnet would pass by the Hall effect sensor.
This would cause the Hall effect sensor to send a pulse to the Arduino, which would then cause an interrupt to trigger a counter. The counter would be used to measure the total distance travelled.

Furthermore, knowing how frequently the tire rotated allowed me to calculate the current velocity of the bike. To get the most accurate readings, this was updated every two seconds.

In the end, the final product looked like this and displayed Distance travelled (km), velocity (km/h), and time (h:mm).

![unnamed](https://user-images.githubusercontent.com/14278780/51433899-7d5cdf80-1c0a-11e9-8c58-6eea8e731214.jpg)
