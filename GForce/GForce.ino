#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

#define LED 2 //Define blinking LED pin

Adafruit_MPU6050 mpu;

// Wifi parameters
const char *ssid = "manupi-connect";
const char *password = "manupi123";

const int MPU_addr=0x68;

float accX=0;
float accY=0;
float accZ=0;

/*
* Connect your controller to WiFi
*/
bool connectToWiFi() {
  WiFi.begin(ssid, password);
  int retries = 0;
  while ((WiFi.status() != WL_CONNECTED) && (retries < 15)) {
    retries++;
    delay(500);
    Serial.print(".");
  }
  if (retries > 14) {
    return false;
  }
  else if (WiFi.status() == WL_CONNECTED) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT); // Initialize the LED pin as an output

  // Establish connection to hotspot to transfer data
  if (connectToWiFi()){
    digitalWrite(LED, LOW); // Turn the LED on by making the voltage LOW
    delay(2000); // Wait for two seconds
  }
  digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  Serial.println("MPU6050 Found!");

  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH
}

sensors_event_t a, g, t;

int min_width=3;
int num_digits_after_decimal=3;

char strXAcc[20], strYAcc[20], strZAcc[20], data[60];

void loop() {
  mpu.getEvent(&a, &g, &t);


  accX = a.acceleration.x;
  accY = a.acceleration.y;
  accZ = a.acceleration.z;
  
  dtostrf(accX, min_width, num_digits_after_decimal, strXAcc);
  dtostrf(accY, min_width, num_digits_after_decimal, strYAcc);
  dtostrf(accZ, min_width, num_digits_after_decimal, strZAcc);

  sprintf(data, "#%s@%s$%s", strXAcc, strYAcc, strZAcc);
  Serial.println(data);
}