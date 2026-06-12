#include <Arduino.h>
#include <WiFi.h>

void setup()
{
  Serial.begin(115200);
  Serial.println("Board starting up...");
  delay(1000);
  Serial.println("Starting WiFi scan...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks < 0)
  {
    Serial.println("WiFi scan failed");
    return;
  }
  Serial.println("Scan complete.");
  Serial.print("Number of networks found: ");
  Serial.println(numNetworks);
}

void loop()
{
  // put your main code here, to run repeatedly:
}