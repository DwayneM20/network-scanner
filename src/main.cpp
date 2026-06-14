#include <Arduino.h>
#include <WiFi.h>

const char *authModeToString(wifi_auth_mode_t mode)
{
  switch (mode)
  {
  case WIFI_AUTH_OPEN:
    return "Open";
  case WIFI_AUTH_WEP:
    return "WEP";
  case WIFI_AUTH_WPA_PSK:
    return "WPA-PSK";
  case WIFI_AUTH_WPA2_PSK:
    return "WPA2-PSK";
  case WIFI_AUTH_WPA_WPA2_PSK:
    return "WPA/WPA2-PSK";
  case WIFI_AUTH_WPA2_ENTERPRISE:
    return "WPA2-Enterprise";
  case WIFI_AUTH_WPA3_PSK:
    return "WPA3-PSK";
  case WIFI_AUTH_WPA2_WPA3_PSK:
    return "WPA2/WPA3-PSK";
  default:
    return "Unknown";
  }
}

void performScan()
{
  Serial.println("Starting WiFi scan...");
  delay(1000);
  int numNetworks = WiFi.scanNetworks(false, true);
  if (numNetworks < 0)
  {
    Serial.println("WiFi scan failed");
    WiFi.scanDelete();
    return;
  }
  else if (numNetworks == 0)
  {
    Serial.println("No networks found.");
    WiFi.scanDelete();
    return;
  }
  Serial.println("Scan complete.");
  Serial.print("Number of networks found: ");
  Serial.println(numNetworks);
  Serial.println("#  RSSI  CH  SECURITY       SSID");
  Serial.println("-- ----- --- -------------- ----------------");
  for (int i = 0; i < numNetworks; ++i)
  {
    String ssid = WiFi.SSID(i);
    if (ssid.length() == 0)
    {
      ssid = "<hidden>";
    }
    Serial.printf("%-3d %-5d %-3d  %-15s %s\n", i + 1, WiFi.RSSI(i), WiFi.channel(i), authModeToString(WiFi.encryptionType(i)), ssid.c_str());
  }
  WiFi.scanDelete();
  Serial.println("Scan results released");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Board starting up...");
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  performScan();
  Serial.println("Press r to scan again");
}

void loop()
{
  if (Serial.available() > 0)
  {
    char command = Serial.read();
    if (command == 'r' || command == 'R')
    {
      performScan();
      Serial.println("Press r to scan again");
    }
  }
}