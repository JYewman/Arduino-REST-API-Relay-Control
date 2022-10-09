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

byte mac[] = {
    0xFE, 0x4E, 0x0C, 0xB7, 0xA7, 0x08};

EthernetServer server(80);

void getIP()
{
    Serial.print("IP address: ");
    Serial.println(Ethernet.localIP());
    Serial.print("Gateway IP: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("Subnet Mask: ");
    Serial.println(Ethernet.subnetMask());
}

void setup()
{
    Ethernet.init(10); // Most Arduino shields
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
}

void loop()
{
    EthernetClient client = server.available();
    if (client)
    {
        boolean currentLineIsBlank = true;
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                Serial.write(c);
                if (c == '\n' && currentLineIsBlank)
                {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close"); // the connection will be closed after completion of the response
                    client.println("Refresh: 5");        // refresh the page automatically every 5 sec
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    // output the value of each analog input pin
                    for (int analogChannel = 0; analogChannel < 6; analogChannel++)
                    {
                        client.print("<h1>Hello world!</h1>");
                    }
                    client.println("</html>");
                    break;
                }
                if (c == '\n')
                {
                    // you're starting a new line
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
        Serial.println("client disconnected");
    }
}