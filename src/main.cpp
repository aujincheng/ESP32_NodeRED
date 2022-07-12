#include<Arduino.h>
#include<WiFi.h>
#include<PubSubClient.h>

// WiFi
//const char* ssid = "jin";
//const char* password = "simplyput123";
const char* ssid = "sl2523@unifi";
const char* password = "0124362208";

// MQTT
const char* mqtt_server = "192.168.0.108";
//IPAddress mqtt_server = (127, 0, 0, 1);

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
void reconnect();
void setup_wifi();

void setup()
{

    Serial.begin(115200);
    pinMode(4,OUTPUT);

    setup_wifi();

    client.setServer(mqtt_server, 1883);
    client.subscribe("esp32/output");
    client.connect("esp32/output");

}

void loop()
{
    if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(1000);

  client.publish("esp32/temperature","21.6");

    
    
  }


void setup_wifi()
{
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect("esp32"))
    {
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}