#include <EEPROM.h>
#include <SPI.h>
#include <WiFi.h>
#include <ArduinoJson.h>

/* ESP8266 Led Hat
 * ===============
 * 
 * Dependencies: 
 * - Arduino core for ESP8266 https://github.com/esp8266/Arduino (Install with Boards Manager)
 * - ArduinoJSON https://github.com/bblanchon/ArduinoJson/wiki (Install with Library Manager)
 */

#define CONFIG_VERSION "v01"
#define CONFIG_START 32

struct Settings {
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

  char config_version[4];
};

//Create default settings
Settings settings = {
  0, //mode
  "LedHat", //ssid
  "fap", //pass

  "LedHat 2", //host_ssid
  "fapfap", //host_pass
  "10.0.0.1", //host_ip

  1, //led_mode
  1, //led_speed

  0, //led_r
  255, //led_g
  0, //led_b

  CONFIG_VERSION //used for validating EEPROM read
};

void loadConfig() {
  Serial.println("Loading configuration from EEPROM");
  if (//EEPROM.read(CONFIG_START + sizeof(settings) - 1) == settings.version_of_program[3] // this is '\0'
      EEPROM.read(CONFIG_START + sizeof(settings) - 2) == settings.version_of_program[2] &&
      EEPROM.read(CONFIG_START + sizeof(settings) - 3) == settings.version_of_program[1] &&
      EEPROM.read(CONFIG_START + sizeof(settings) - 4) == settings.version_of_program[0])
  { 
    //Version was ok. Read settings.
    for (unsigned int t=0; t<sizeof(settings); t++) 
    {
      *((char*)&settings + t) = EEPROM.read(CONFIG_START + t);
    }
    Serial.println("Configuration read.");
  } else {
    //Version number not found. Overwrite settings.
    Serial.println("Configuration not found.");
    saveConfig();
    
  }
}

void saveConfig() {
  Serial.println("Writing configuration to EEPROM.");
  for (unsigned int t=0; t<sizeof(settings); t++)
  {
    //Write to EEPROM
    EEPROM.write(CONFIG_START + t, *((char*)&settings + t));
    //Verify data
    if (EEPROM.read(CONFIG_START + t) != *((char*)&settings + t))
    {
      Serial.println("ERROR: Writing to EEPROM failed!");
      return;
    }
  }
}
void setup() {
  Serial.begin(9600);
  loadConfig();
}

void loop() {
  Serial.println(settings.ssid);
  delay(1000);
}
