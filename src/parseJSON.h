#include <Arduino.h>



bool readForecast(String jsonMessage)
{
//  Serial.print(jsonMessage);

    int out = 0;
        // debug
        utft.setBackColor(120,120,110);
        utft.fillRect( 0, 0 , 199,23);
        uText.print(25, 10, "read Forecast");

       



    if (jsonMessage.indexOf("cod") > 0){

            DynamicJsonDocument doc(400);

            deserializeJson(doc,jsonMessage);


float temp = doc["temp"];
float temp_min = doc["temp_min"];
float temp_max = doc["temp_max"];
float pressure = doc["pressure"];
float humidity = doc["humidity"];
float feels_like = doc["feels_like"];



                temp_outside_today = temp;
                temp_outside_feels_like_today = feels_like;
                temp_min_today = temp_min;
                temp_max_today = temp_max;
                presure_today =  pressure; // 1033
                humidity_today = humidity; // 84


   }
  
    return 1;
  };

