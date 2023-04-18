
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <Wire.h>
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(4,5);

// Kredensial WiFi
const char* ssid     = "xxxxxx";
const char* password = "xxxxxx";

// Domain server hosting
const char* serverName = "http://www.xxxxx.xxx/xxxxxxxx.php"; //example: "https://www.rizzsmartenergy.com/post-my-data.php"

//Kode API untuk akses MySQL
String apiKeyValue = "y0urAPI6x4!";

String homeName = "My Home";

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, serverName);
    
    // Menentukan header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Data yang di post (HTTP POST)
    String httpRequestData = "api_key=" + apiKeyValue + "&Home=" + homeName
                          + "&Voltage=" + String(pzem.voltage()) + "&Current=" + String(pzem.current())
                          + "&Power=" + String(pzem.power()) + "&Energy=" + String(pzem.energy())
                          + "&Frequency=" + String(pzem.frequency()) + "&PF=" + String(pzem.pf())+ "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 2 seconds
  delay(2000);  
}
