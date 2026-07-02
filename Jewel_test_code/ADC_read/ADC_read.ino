#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

#define SDA_PIN 23
#define SCL_PIN 22

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ADS1115 Test");

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize ADS1115
  if (!ads.begin(0x49)) {
    Serial.println("Failed to initialize ADS1115!");
    while (1);
  }

  Serial.println("ADS1115 Found!");

  // Gain settings:
  // GAIN_TWOTHIRDS = +/-6.144V
  // GAIN_ONE       = +/-4.096V
  // GAIN_TWO       = +/-2.048V
  // GAIN_FOUR      = +/-1.024V
  // GAIN_EIGHT     = +/-0.512V
  // GAIN_SIXTEEN   = +/-0.256V

  ads.setGain(GAIN_ONE);   // ±4.096V

  Serial.println("Starting measurements...");
}

void loop() {

  int16_t adc0 = ads.readADC_SingleEnded(0);
  int16_t adc1 = ads.readADC_SingleEnded(1);
  int16_t adc2 = ads.readADC_SingleEnded(2);
  int16_t adc3 = ads.readADC_SingleEnded(3);

  float ch0 = ads.computeVolts(adc0);
  float ch1 = ads.computeVolts(adc1);
  float ch2 = ads.computeVolts(adc2);
  float ch3 = ads.computeVolts(adc3);

  Serial.println("----------------------------------------");
  Serial.printf("AIN0: %6d   %.4f V\n", adc0, ch0);
  Serial.printf("AIN1: %6d   %.4f V\n", adc1, ch1);
  Serial.printf("AIN2: %6d   %.4f V\n", adc2, ch2);
  Serial.printf("AIN3: %6d   %.4f V\n", adc3, ch3);

  delay(1000);
}