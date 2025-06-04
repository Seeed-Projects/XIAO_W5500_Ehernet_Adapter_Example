/*
  This sketch will log Ethernet events to the serial console
  It will also log the MAC address and current IP address every second (IP can be assigned by DHCP)
*/
#include <SPI.h>
#include <ETH.h>
#include <WiFi.h>

static bool eth_connected = false;

#ifndef ETH_PHY_CS
#define ETH_PHY_TYPE ETH_PHY_W5500
#define ETH_PHY_ADDR 1
#define ETH_PHY_CS   D1
#define ETH_PHY_IRQ  -1
#define ETH_PHY_RST  -1
#endif

// SPI pins
#define ETH_SPI_SCK  D8
#define ETH_SPI_MISO D9
#define ETH_SPI_MOSI D10


// React to Ethernet events:
void onEvent(arduino_event_id_t event, arduino_event_info_t info)
{
  switch (event) {

    case ARDUINO_EVENT_ETH_START:
      // This will happen during setup, when the Ethernet service starts
      Serial.println("ETH Started");
      //set eth hostname here
      ETH.setHostname("esp32-ethernet");
      break;

    case ARDUINO_EVENT_ETH_CONNECTED:
      // This will happen when the Ethernet cable is plugged 
      Serial.println("ETH Connected");
      break;

    case ARDUINO_EVENT_ETH_GOT_IP:
    // This will happen when we obtain an IP address through DHCP:
      Serial.print("Got an IP Address for ETH MAC: ");
      Serial.print(ETH.macAddress());
      Serial.print(", IPv4: ");
      Serial.print(ETH.localIP());
      if (ETH.fullDuplex()) {
        Serial.print(", FULL_DUPLEX");
      }
      Serial.print(", ");
      Serial.print(ETH.linkSpeed());
      Serial.println("Mbps");
      eth_connected = true;

      // Uncomment to automatically make a test connection to a server:
      // testClient( "192.168.0.1", 80 );

      break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
      // This will happen when the Ethernet cable is unplugged 
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;

    case ARDUINO_EVENT_ETH_STOP:
      // This will happen when the ETH interface is stopped but this never happens
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;

    default:
      break;
  }
}

// Try to read something from a webserver:
void testClient(const char * host, uint16_t port)
{
  Serial.print("\nConnecting to ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);

  NetworkClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  client.printf("GET / HTTP/1.1\r\nHost: %s\r\n\r\n", host);
  while (client.connected() && !client.available());
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("closing connection\n");
  client.stop();
}

// Initializing everything at start up / after reset:
void setup()
{
  // Wait for the hardware to initialize:
  delay(500);

  // This sketch will log some information to the serial console:
  Serial.begin(115200); // Assuming computer will be connected to serial port at 115200 bauds
  Serial.println("Setup...");
  
  Serial.println("Registering event handler for ETH events...");
  Network.onEvent(onEvent);
  
  // Starth Ethernet (this does NOT start WiFi at the same time)
  Serial.println("Starting ETH interface...");
  SPI.begin(ETH_SPI_SCK, ETH_SPI_MISO, ETH_SPI_MOSI);
  ETH.begin(ETH_PHY_TYPE, ETH_PHY_ADDR, ETH_PHY_CS, ETH_PHY_IRQ, ETH_PHY_RST, SPI);

  Serial.println("Waiting for Ethernet connection");
  while (!eth_connected) {
    delay(500);
    Serial.print(".");
  }
}


void loop()
{
  if (eth_connected) {
    testClient("baidu.com", 80);
  }
  delay(20000);
}
