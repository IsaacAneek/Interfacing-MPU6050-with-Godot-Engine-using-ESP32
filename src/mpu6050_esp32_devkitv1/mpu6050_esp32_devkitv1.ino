#include <Wire.h>
#include <ReefwingMPU6050.h>
#include <ArduinoJson.h>
#include <NetworkUdp.h>
#include <WiFi.h>

//  WiFi network name and password:
const char *networkName = "";
const char *networkPswd = "";

//  IP address to send UDP data to:
//  either use the ip address of the of the device you are gonna send data to or
//  a network broadcast address
const char *udpAddress = "";
const int udpPort = 3333;

//  Are we currently connected?
boolean connected = false;

//  The udp library class
NetworkUDP udp;

//  Our imu class that will be responsible for handling the mpu6050
ReefwingMPU6050 imu;

//  Timers
unsigned long timer = 0;
float timeStep = 0.01;

//  Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

float angleX_offset = 0;
float angleY_offset = 0;
float angleZ_offset = 0;

void connectToWiFi(const char *ssid, const char *pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);  // Will call WiFiEvent() from another thread.

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

// WARNING: WiFiEvent is called from a separate FreeRTOS task (thread)!
void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      //When connected set
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      //initializes the UDP state
      //This initializes the transfer buffer
      udp.begin(WiFi.localIP(), udpPort);
      connected = true;
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connected = false;
      break;
    default: break;
  }
}


void setup(void) {
  Serial.begin(115200);

  connectToWiFi(networkName, networkPswd);
  
  imu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);

  //  Start Serial and wait for connection
  while (!Serial);

  if (imu.connected()) {
    Serial.println("MPU6050 IMU Connected."); 

    //  Set sensitivity threshold (default) and calibrate
    imu.setThreshold(3);
    imu.calibrateGyro();
    delay(20);

    //  Flush the first reading - this is important!
    //  Particularly after changing the configuration.
    imu.readRawGyro();
  } else {
    Serial.println("MPU6050 IMU Not Detected.");
    while(1);
  }
}

void loop() {
  timer = millis();

  //  Read normalized values
  ScaledData norm = imu.readNormalizeGyro();

  //  Calculate Pitch, Roll and Yaw
  //  Need to integrate gyro rates (DPS) to get Degrees
  pitch = pitch + norm.sy * timeStep;
  roll = roll + norm.sx * timeStep;
  yaw = yaw + norm.sz * timeStep;
  
  //  Serialize the angle values into JSON
  JsonDocument doc;

  JsonArray data = doc["data"].to<JsonArray>();
  data.add(pitch);
  data.add(roll);
  data.add(yaw);
  
  //  This array will contain the JSON data and this array will actually be passed through UDP
  char output[64];

  //  doc.shrinkToFit();  // optional
  //  Send this JSON packet through UDP
  //  Max size of the packet to send through UDP?
  //  Optimize serialization performance https://arduinojson.org/v7/how-to/improve-speed/
  serializeJson(doc, output);

  Serial.println(output);
  Serial.println("");

  //  only send data when connected
  if (connected) {
  //  Send a packet
    udp.beginPacket(udpAddress, udpPort);
    udp.printf(output);
    udp.endPacket();
  }
}