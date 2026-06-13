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
  for (int i = 0; i < numNetworks; ++i)
  {
    Serial.print("Network ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.print(" dBm) ");
    Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured");
    Serial.println();
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
}