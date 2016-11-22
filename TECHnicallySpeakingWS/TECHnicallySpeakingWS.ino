/*
  Simple WebSocket client for ArduinoHttpClient library
  Connects to the WebSocket server, and sends a hello
  message every 5 seconds
  note: WiFi SSID and password are stored in config.h file.
  If it is not present, add a new tab, call it "config.h"
  and add the following variables:
  char ssid[] = "ssid";     //  your network SSID (name)
  char pass[] = "password"; // your network password
  created 28 Jun 2016
  by Sandeep Mistry
  this example is in the public domain

  Combines some code from Tom Igoe's Wifi101 example

  Modified by OllieBck 19 November 2016 to work with Websocket Server

*/

#include <SPI.h>
#include <WiFi101.h>
#include <ArduinoHttpClient.h>
#include "config.h"

/* //for DigitalOcean
  char serverAddress[] = "job271.itp.io";
  int port = 9876;
*/

  // or
  IPAddress server(159,203,190,133);       // address of the server
  int port = 9111; //change back to 9876



/*
  // for PhoneGap
  char serverAddress[] = "192.168.1.3";
  int port = 3000;
*/

 /*
IPAddress server(192, 168, 1, 3);    // address of the server
int port = 3000;
*/

WiFiClient wifi;                // instance of the WIFi client library
WebSocketClient client = WebSocketClient(wifi, server, port);
int status = WL_IDLE_STATUS;      // WiFi status

const int connectionLED = 6;      // this LED indicates whether you're connected
const int lightPin = 7;
const int tvPin = 5;

const int sendInterval = 100;     // minimum time between messages to the server
const int debounceInterval = 15;  // used to smooth out pushbutton readings
int prevButtonState = 0;          // previous state of the pushbutton
long lastTimeSent = 0;            // timestamp of the last server message

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // initialize digital inputs and outputs:
  pinMode(connectionLED, OUTPUT);
  pinMode(tvPin, OUTPUT);
  pinMode(lightPin, OUTPUT);

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 3 seconds for connection:
    delay(3000);
  }

  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  client.begin();
  while (client.connected()) {
    /*
    //Serial.print("connected");
    if (digitalRead(connectButton) == LOW) {
      Serial.println("press");
      //client.begin();
      delay(50);

      // send a hello #
      client.beginMessage(TYPE_TEXT);
      client.print("on");
      client.endMessage();
    }
  */
    messageRec();

    delay(100);
  }
  Serial.println("disconnected");
  digitalWrite(connectionLED, LOW);
}

void messageRec() {
  // check if a message is available to be received
  int messageSize = client.parseMessage();
  String message;

  if (messageSize > 0) {
    Serial.println("Received a message:");
    String message = client.readString();
    if (message == "connected") {
      digitalWrite(connectionLED, HIGH);
    }
    if (message == "light on") {
      digitalWrite(lightPin, HIGH);
    }
    if (message == "light off") {
      digitalWrite(lightPin, LOW);
    }
    if (message == "tv on") {
      digitalWrite(tvPin, HIGH);
    }
    if (message == "tv off") {
      digitalWrite(tvPin, LOW);
    }
    Serial.println(message);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
