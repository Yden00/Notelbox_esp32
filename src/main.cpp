#include "LedControl.h"
#include "FanControl.h"
#include <Adafruit_SHT31.h>
#include <SPI.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>

const char *ssid = "Notel_OFFICE";
const char *password = "7222ce33";

LedControl ledControl(2, 33);
FanControl fanControl(0, 50, 26, 8);
Adafruit_SHT31 sht31;

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  ArduinoOTA.setPort(3232);
  ArduinoOTA.setHostname("notelbox_esp32");
  ArduinoOTA.setPassword("admin");

  ArduinoOTA.onStart([]()
  {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type); });

  ArduinoOTA.onEnd([](){ Serial.println("\nEnd"); });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total){ Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });

  ArduinoOTA.onError([](ota_error_t error)
  {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    } 
  });

  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ request->send(200, "text/plain", "Hello, ESP32!"); });
  server.begin();
  Serial.println("Web server started");

  pinMode(25, OUTPUT);
  ledControl.setup();
  fanControl.setup();
  Wire.begin(14, 27);
  Serial.begin(9600);
  bool sensorWorking = sht31.begin(0x44);
  ledControl.setStatusColor(sensorWorking);
}

void loop()
{
  ArduinoOTA.handle();
  float temperature = sht31.readTemperature();
  fanControl.charging_control(temperature);
  float humidity = sht31.readHumidity();
  ledControl.setTemperatureColor(temperature);
  fanControl.setFanSpeed(temperature);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Fan Speed: ");
  Serial.print(fanControl.getFanSpeed());
  Serial.println(" / 255");
  Serial.println(WiFi.localIP());
  delay(1000);
}
