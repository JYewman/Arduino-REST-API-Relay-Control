/*
 * File: c:\Users\joshu\OneDrive - goSystem Solutions Limited\Documents\Programming\Private\bathroom-light-control\bathroom-light-control.ino
 * Project: c:\Users\joshu\OneDrive - goSystem Solutions Limited\Documents\Programming\Private\bathroom-light-control
 * Created Date: Sunday, October 9th 2022, 5:45:13 pm
 * Author: Joshua Yewman
 * Author Email: joshua@gosystem.co.uk
 * -----
 * Last Modified:
 * Modified By:
 * -----
 * Copyright (c) 2022 goSysten Solu#tions Limited
 */

#include <SPI.h>
#include <Ethernet.h>
#include <Log.h>
#include <RestServer.h>
#include <RestSettings.h>

byte mac[] = {
    0xFE, 0x4E, 0x0C, 0xB7, 0xA7, 0x08};

#define RELAY_ON LOW
#define RELAY_OFF HIGH
int relayPin = 7;
int relayState = RELAY_OFF;

EthernetServer server(80);
RestServer rest(server);

void setRelay(char *params = "")
{
    if (strncmp(params, "active=1", 8) == 0)
    {
        relayState = RELAY_ON;
        DLOG("on");
        digitalWrite(relayPin, relayState);
    }
    else if (strncmp(params, "active=0", 8) == 0)
    {
        relayState = RELAY_OFF;
        DLOG("off");
        digitalWrite(relayPin, relayState);
    }

    rest.addData("active", !relayState);
}

void getRelay(char *params = "")
{
    rest.addData("active", !relayState);
}

void getIP()
{
    Serial.print("IP address: ");
    Serial.println(Ethernet.localIP());
    Serial.print("DNS Server: ");
    Serial.println(Ethernet.dnsServerIP());
    Serial.print("Gateway IP: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("Subnet Mask: ");
    Serial.println(Ethernet.subnetMask());
}

void setup()
{
    LOG_SETUP();
    LOG("Init...");
    Ethernet.init(10);
    Serial.begin(115200);
    Serial.println("Initialize Ethernet with DHCP:");
    if (Ethernet.begin(mac) == 0)
    {
        Serial.println("Failed to configure Ethernet using DHCP");
        if (Ethernet.hardwareStatus() == EthernetNoHardware)
        {
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        }
        else if (Ethernet.linkStatus() == LinkOFF)
        {
            Serial.println("Ethernet cable is not connected.");
        }
        // no point in carrying on, so do nothing forevermore:
        while (Ethernet.hardwareStatus() == LinkOFF)
        {
            Serial.println("Unable to connect to network, retry in 15 seconds...");
            delay(15000);
        }
    }
    getIP();
    server.begin();
    Serial.print("Web Server Started @ ");
    Serial.println(Ethernet.localIP());
    Serial.print("Server is at ");
    Serial.println(Ethernet.localIP());

    // Add routes to the REST Server
    rest.addRoute(POST, "/relayPin", setRelay);
    rest.addRoute(GET, "/relayPin", getRelay);

    // Setup relayPin and other sensors
    pinMode(relayPin, OUTPUT);         // Set Pin7 as output
    digitalWrite(relayPin, RELAY_OFF); // Turn off relayPin
}

void loop()
{
    // Run the RestServer
    rest.run();
}
