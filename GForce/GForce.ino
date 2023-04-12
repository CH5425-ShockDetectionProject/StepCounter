#include <Adafruit_MPU6050.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

#define LED 2 //Define blinking LED pin

Adafruit_MPU6050 mpu;

// Wifi parameters
const char *ssid = "manupi-connect";
const char *password = "manupi123";

// TCP
int port = 8888;  //Port number
WiFiServer server(port);

const int MPU_addr=0x68;

float accX=0, accY=0, accZ=0, gyroX = 0, gyroY = 0, gyroZ = 0;

/*
* Connect your controller to WiFi
*/
bool connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());       // Send the IP address of the ESP8266 to the computer
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

  // Finding MPU6050 and Initialising
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  digitalWrite(LED, HIGH); // Turn the LED off by making the voltage HIGH

  // Start the server
  server.begin();
}

sensors_event_t a, g, t;

int min_width=3;
int num_digits_after_decimal=3;

char strXAcc[20], strYAcc[20], strZAcc[20], strXgyro[20], strYgyro[20], strZgyro[20], data[60];

void loop() {
  WiFiClient client = server.available();
  if (client) {
    if(client.connected()){
      Serial.println("Client Connected");
    }
    while(client.connected()){      
      // Fetch all sensor data from MPU6050
      mpu.getEvent(&a, &g, &t);
      accX = a.acceleration.x;
      accY = a.acceleration.y;
      accZ = a.acceleration.z;
      gyroX = g.gyro.x;
      gyroY = g.gyro.y;
      gyroZ = g.gyro.z;
      dtostrf(accX, min_width, num_digits_after_decimal, strXAcc);
      dtostrf(accY, min_width, num_digits_after_decimal, strYAcc);
      dtostrf(accZ, min_width, num_digits_after_decimal, strZAcc);
      dtostrf(gyroX, min_width, num_digits_after_decimal, strXgyro);
      dtostrf(gyroY, min_width, num_digits_after_decimal, strYgyro);
      dtostrf(gyroZ, min_width, num_digits_after_decimal, strZgyro);
      sprintf(data, "%s,%s,%s,%s,%s,%s\n", strXAcc, strYAcc, strZAcc, strXgyro, strYgyro, strZgyro);

      //Send Data to connected client
      client.write(data);
    }
    client.stop();
    Serial.println("Client disconnected");
  }
  // Serial.println(data);
}