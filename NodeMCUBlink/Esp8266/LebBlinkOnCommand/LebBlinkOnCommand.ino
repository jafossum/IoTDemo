/***************************************************
  Modified from
  Adafruit MQTT Library ESP8266 Example
  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino
  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821
  Adafruit invests time and resources provid<ing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Secrets.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       WIFI_SSID
#define WLAN_PASS       WIFI_PASSWORD

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "iot-raspi.local"
#define AIO_SERVERPORT  1883           // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'heartbeat' for publishing.
Adafruit_MQTT_Publish hbFeed = Adafruit_MQTT_Publish(&mqtt, "heartbeat");

// Setup a feed called 'ledStatus' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffled = Adafruit_MQTT_Subscribe(&mqtt, "ledStatus");

/*************************** Sketch Code ************************************/

void MQTT_connect();

#define LED D0 // Pin with LED on NodeMCU

void ledStatusCallback(char* payload, uint16_t length) {

 Serial.print("Message arrived [ledStatus]");

 for (int i=0;i<length;i++) {
   char receivedChar = (char)payload[i];
   Serial.println(receivedChar);
   if (receivedChar == '0')
     // ESP8266 outputs are "reversed"
     digitalWrite(LED, HIGH);
   if (receivedChar == '1')
     digitalWrite(LED, LOW);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED, OUTPUT);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  //WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Set callback
  onoffled.setCallback(ledStatusCallback);

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffled);
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // HeartBeat the client(s) to let them know unit is alive
  hbFeed.publish("IOT-Device1");

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(10000);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT ");
  Serial.println(AIO_SERVER);

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}