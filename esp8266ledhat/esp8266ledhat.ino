#include <EEPROMex.h>
#include <EEPROMVar.h>

#include <SPI.h>
#include <WiFi.h>
#include <ArduinoJson.h>

/* ESP8266 Led Hat
 * ===============
 * 
 * Dependencies: 
 * - Arduino core for ESP8266 https://github.com/esp8266/Arduino (Install with Boards Manager)
 * - ArduinoJSON https://github.com/bblanchon/ArduinoJson/wiki (Install with Library Manager)
 * - EEPROMex https://github.com/thijse/Arduino-EEPROMEx (Install with Library Manager)
 */

#define CONFIG_ADDRESS 0
#define CONFIG_VERSION "v01"

//Start server on port 80
WiFiServer server(80);

struct Settings {
  char config_version[4];
  int mode;
  char ssid[32];
  char pass[32];
  
  char host_ssid[32];
  char host_pass[32];
  char host_ip[15];

  int led_mode;
  int led_speed;
  
  byte led_r;
  byte led_g;
  byte led_b;
};

Settings settings;

void loadConfig() {
  EEPROM.readBlock(CONFIG_ADDRESS, settings);

  if(strcmp(settings.config_version, "fukkushimoiajsdofijasdfoijasdfa") != 0){
    Serial.println("Configuration not found.");

    Serial.println("Writing default settings to EEPROM.");

    //Create default settings
    Settings default_settings = {
      CONFIG_VERSION,
      0, //mode
      "LedHat", //ssid
      "fapfapfap", //pass
    
      "LedHat Master", //host_ssid
      "fapfapfapfap", //host_pass
      "10.0.1.1", //host_ip
    
      1, //led_mode
      1, //led_speed
    
      0, //led_r
      255, //led_g
      0 //led_b
    };
  
    //Copy default settings to settings
    memcpy(&settings, &default_settings, sizeof(Settings));
    
    EEPROM.writeBlock(CONFIG_ADDRESS, settings);
  } else {
    Serial.println("Configuration read with correct version number.");
  } 
  
}

void setupWiFiAP() {
  WiFi.mode(WIFI_AP);

  //Set MAC address
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);

  //Set AP configuration
  IPAddress ip(10, 0, 0, 1);
  IPAddress gateway(10, 0, 0, 1);
  IPAddress mask(255, 255, 255, 0);
  WiFi.softAPConfig(ip, gateway, mask);

  //Start AP
  WiFi.softAP(settings.ssid, settings.pass);

  Serial.println("Started WiFi Access Point, SSID: ");
  Serial.print(settings.ssid);
}

void setup() {
  Serial.begin(9600);
  loadConfig();
  setupWifiAP();
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  delay(1000);
}
