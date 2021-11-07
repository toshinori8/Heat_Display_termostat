#include <Arduino.h>

bool turnValve(String level, String valve, String state){

    // level // valve 1-8 // ON OFF

        Serial.println("- włączam - level ");
        Serial.println(String(level));
        Serial.println("-         - valve ");
        Serial.println(String(valve));

Serial1.println("publish espGatewayMessages/test Hello World!");

Serial1.println("publish home/relay_01/in {'valve':"+String(valve)+",'state':'"+String(state)+"'}");


}