#include "WiFi.h"

// Print
void printCon() {
  CMDSerial.print("WiFi connected: ");
  CMDSerial.println(WiFi.SSID());
}

void printDiscon() {
  CMDSerial.print("Disconnected from ");
  CMDSerial.println(WiFi.SSID());
}

void printIp() {
  CMDSerial.print("IP address: ");
  CMDSerial.println(WiFi.localIP());
}

void printNoWiFi() {
  CMDSerial.println("no WiFi connected");
}

// Command Function
void scanWiFi() {
  WiFi.mode(WIFI_STA);
  CMDSerial.println("scan start");
  int n = WiFi.scanNetworks();
  CMDSerial.println("scan done");
  if (n == 0) {
    CMDSerial.println("no networks found");
  } else {
    CMDSerial.print(n);
    CMDSerial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID for each network found
      CMDSerial.print(i + 1);
      CMDSerial.print(": ");
      CMDSerial.print(WiFi.SSID(i));
      CMDSerial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  CMDSerial.println("");
}

void connectWiFi(String _ssid, String _pass) {
  int N = _ssid.length() + 1,
      M = _pass.length() + 1;

  char ssid[N] ; _ssid.toCharArray(ssid, N);
  char pass[M] ; _pass.toCharArray(pass, M);

  WiFi.disconnect();

  CMDSerial.print("Connecting to ");
  CMDSerial.println(ssid);

  WiFi.begin(ssid, pass);

  for (int i = 0; i < 20; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    CMDSerial.print(".");
    delay(500);
  }
  CMDSerial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    printCon();
    printIp();
  } else {
    CMDSerial.println("can't connect to WiFi");
  }
}

void disconnectWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFi.disconnect();
    printDiscon();
  } else {
    printNoWiFi();
  }
}

void getIp() {
  if (WiFi.status() == WL_CONNECTED) {
    printIp();
  } else {
    printNoWiFi();
  }
}

void getApStat() {
  if (WiFi.status() == WL_CONNECTED) {
    printCon();
    printIp();
  } else {
    printNoWiFi();
  }
}


