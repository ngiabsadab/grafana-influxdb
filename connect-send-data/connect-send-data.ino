
/*  NETPIE ESP8266 basic sample                            */
/*  More information visit : https://netpie.io             */

#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid     = "ngiabsadab";
const char* password = "123456789";

#define APPID   "SmartLiving"
#define KEY     "JFyNXxk8kHsZd01"
#define SECRET  "NiMA4JhAgplL1DsbqaNtT0Td2"
#define ALIAS   "NODEMCU_BAESLab"


const int analogInPin = A0;
int sensorValue = 0;
int outputValue = 0;

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

/* When a microgear is connected, do this */
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
    Serial.println("Connected to NETPIE...");
    /* Set the alias of this microgear ALIAS */
    microgear.setAlias(ALIAS);
}


void setup() {
    /* Add Event listeners */

    /* Call onLostgear() when some gear goes offline */
    microgear.on(ABSENT,onLostgear);

    /* Call onConnected() when NETPIE connection is established */
    microgear.on(CONNECTED,onConnected);

    Serial.begin(115200);
    Serial.println("Starting...");

    /* Initial WIFI, this is just a basic method to configure WIFI on ESP8266.                       */
    /* You may want to use other method that is more complicated, but provide better user experience */
    if (WiFi.begin(ssid, password)) {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* Initial with KEY, SECRET and also set the ALIAS here */
    microgear.init(KEY,SECRET,ALIAS);

    /* connect to NETPIE to a specific APPID */
    microgear.connect(APPID);
}

void loop() {
    /* To check if the microgear is still connected */
      sensorValue = analogRead(analogInPin);      
      outputValue = map(sensorValue, 0, 1023, 0, 255);
      Serial.println("sensor = "+String(outputValue));

    if (microgear.connected()) {
        Serial.println("connected");
        /* Call this method regularly otherwise the connection may be lost */
        microgear.loop();

        if (timer >= 5000) {
            Serial.println("Publish...");
            /* Chat with the microgear named ALIAS which is myself */
            microgear.chat(ALIAS,outputValue);
            timer = 0;
        } 
        else timer += 100;
    }
    else {
        Serial.println("connection lost, reconnect...");
        if (timer >= 5000) {
            microgear.connect(APPID);
            timer = 0;
        }
        else timer += 100;
    }
    delay(100);
}
