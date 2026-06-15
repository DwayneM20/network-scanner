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

bool scanInProgress = false;

void printScanResults(int numNetworks)
{
  if (numNetworks == 0)
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

void startScan()
{
  Serial.println("Starting WiFi scan...");
  int result = WiFi.scanNetworks(true, true);
  if (result == WIFI_SCAN_RUNNING)
  {
    Serial.println("Scan started successfully.");
    scanInProgress = true;
  }
  else if (result == WIFI_SCAN_FAILED)
  {
    Serial.println("Failed to start scan.");
    WiFi.scanDelete();
    scanInProgress = false;
  }
  else if (result >= 0)
  {
    printScanResults(result);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Board starting up...");
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  startScan();
  if (!scanInProgress)
  {
    Serial.println("Press r to scan again");
  }
}

void loop()
{
  if (scanInProgress)
  {
    int result = WiFi.scanComplete();
    if (result == WIFI_SCAN_RUNNING)
    {
    }
    else if (result == WIFI_SCAN_FAILED)
    {
      Serial.println("Scan failed.");
      WiFi.scanDelete();
      scanInProgress = false;
      Serial.println("Press r to scan again");
    }
    else if (result >= 0)
    {
      printScanResults(result);
      scanInProgress = false;
      Serial.println("Press r to scan again");
    }
  }

  if (Serial.available() > 0)
  {
    char command = Serial.read();
    if (command == 'r' || command == 'R')
    {
      if (scanInProgress)
      {
        Serial.println("Scan already in progress; please wait...");
      }
      else
      {
        startScan();
      }
      if (!scanInProgress)
      {
        Serial.println("Press r to scan again");
      }
    }
  }
}