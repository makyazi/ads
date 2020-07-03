#include <ESP8266WiFi.h>
#define HEATER D2

const char* ssid = "esp";
 const char* password = "12345678";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(HEATER, OUTPUT);
  digitalWrite(HEATER,HIGH);
 
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  if (req.indexOf("/heateron") != -1)
  {
     
    digitalWrite(HEATER,LOW);
    Serial.println("HEATER ON");
  }
  else if(req.indexOf("/heateroff") != -1)
  {
    digitalWrite(HEATER,HIGH);
    Serial.println("HETAER OFF");
  }


  
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  /*web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>LED Status</h1>\r\n";
  web += "<p>\r\n";
  if(status_led==1)
      web += "LED On\r\n";
  else
      web += "LED Off\r\n";
  web += "</p>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/ledon\">\r\n";
  web += "<button>LED On</button >\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  
  web += "<a href=\"/ledoff\">\r\n";
  web += "<button>LED Off</button >\r\n";
  web += "</a>\r\n";
  
  web += "</body>\r\n";
  web += "</html>\r\n";
  */
  client.print(web);
}
