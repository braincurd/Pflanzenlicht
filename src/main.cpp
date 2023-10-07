#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN D2 // Change this to the pin connected to your NeoPixel strip
#define NUM_PIXELS 4    // Change this to the number of NeoPixels in your strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int sensorPin = A0; // Analog input pin for the soil moisture sensor

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Read soil moisture sensor value
  int sensorValue = analogRead(sensorPin);

  // Check for extreme values
  if (sensorValue >= 0 && sensorValue <= 1023) {
    // Map the sensor value to a color gradient
    int red = map(sensorValue, 0, 1023, 0, 255); //1023 Maximal Wert 0= Minimalwert
    int green = map(sensorValue, 0, 1023, 255, 0);
    int blue = 0;

    // Set NeoPixel color
    for (int i = 0; i < NUM_PIXELS; i++) {
      strip.setPixelColor(i, red, green, blue);
    }
    strip.show();

    // Print sensor value to serial monitor
    Serial.print("Soil Moisture: ");
    Serial.println(sensorValue);
  } else {
    // Handle extreme values (e.g., sensor disconnected)
    Serial.println("Sensor Error");
    // You can set a specific color or take other actions as needed
  }

  delay(10); // Delay for 1 second before the next reading
}
