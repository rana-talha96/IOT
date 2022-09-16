#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "Adafruit_MQTT.h"

#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID ""

#define WLAN_PASS ""

#define AIO_SERVER "io.adafruit.com"

#define AIO_SERVERPORT 1883 

#define AIO_USERNAME "divisible"

#define AIO_KEY "48b4eadf808542eea1d18ec15b113d6e"

int output=2;

WiFiClient client; // Create an ESP8266 WiFiClient class to connect to the MQTT server.

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY); // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.

Adafruit_MQTT_Subscribe light_control = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light_control");

void MQTT_connect();

void setup() {

Serial.begin(115200);
WiFiManager wifiManager;
wifiManager.autoConnect("AutoConnectAP");
Serial.println("wifi connected... ");
delay(10);

pinMode(14,OUTPUT);

// Connect to WiFi access point.

Serial.println(); Serial.println();

Serial.print("Connecting to ");

Serial.println(WLAN_SSID);



WiFi.begin(WLAN_SSID, WLAN_PASS);

while (WiFi.status() != WL_CONNECTED) {

delay(500);

Serial.print(".");

}

Serial.println();

Serial.println("WiFi connected");

Serial.println("IP address: "); Serial.println(WiFi.localIP());

mqtt.subscribe(&light_control);

}

uint32_t x=0;

void loop() {
Serial.println(14);
MQTT_connect();

Adafruit_MQTT_Subscribe *subscription;

while ((subscription = mqtt.readSubscription(5000))) {

if (subscription == &light_control) {

Serial.print(F("Got: "));

Serial.println((char *)light_control.lastread);

if (!strcmp((char*) light_control.lastread, "ON"))

{

digitalWrite(14, LOW);

}

else

{

digitalWrite(14, HIGH);

}

}

}





}

void MQTT_connect() {

int8_t ret;

// Stop if already connected.

if (mqtt.connected()) {

return;

}

Serial.print("Connecting to MQTT... ");

uint8_t retries = 3;

while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected

Serial.println(mqtt.connectErrorString(ret));

Serial.println("Retrying MQTT connection in 5 seconds...");

mqtt.disconnect();

delay(5000); // wait 5 seconds

retries--;

if (retries == 0) {

// basically die and wait for WDT to reset me

while (1);

}

}

Serial.println("MQTT Connected!");

}
