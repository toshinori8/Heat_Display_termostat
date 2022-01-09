#include <Arduino.h>

bool turnValve(String level, String valve, String state)
{

    // level // valve 1-8 // ON OFF
 
   
    Serial.println("Valve controll");
    Serial.println("valve : " + String(valve)+" state : "+ String(state));
    Serial.println("Valve controll");

        Serial1.println("publish home/relay_01/in {'valve':" + String(valve) + ",'state':'" + String(state) + "'}");
}

bool sendWhitelist()
{

    Serial.println("|||||||");
    Serial1.println("publish home/MQTTGateway/commands/MQTTtoBT/config {\"hasspresence\":false, \"interval\":5000}");
    delay(500);
    
    
    Serial1.println("publish home/MQTTGateway/commands/MQTTtoBT/config {\"white-list\":[" + WhiteList + "\"]}");
    Serial.println("Publish BLE gateway config");
    Serial.println("publish home/MQTTGateway/commands/MQTTtoBT/config {\"white-list\":[" + WhiteList + "\"]}");

    // WhiteList
}