#include <Arduino.h>
#include <StreamUtils.h>

bool readForecast(String jsonMessage) 
{

//jsonMessage.replace("\"", R"(\")");

Serial.println(jsonMessage);

StaticJsonDocument<1536> doc;
DeserializationError error = deserializeJson(doc, jsonMessage.c_str());
if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.c_str());
}


//const char* cod = doc["cod"]; // "200"
//int message = doc["sunrise"]; // 0
//int temp = doc["temp"]; // 3

  // Extract values
  // Serial.println(F("Response:"));
  // Serial.println(doc["sensor"].as<char*>());
  // Serial.println(doc["time"].as<long>());
  // Serial.println(doc["data"][0].as<float>(), 6);
  // Serial.println(doc["data"][1].as<float>(), 6);

// Serial.print(doc["cod"].c_str());
// Serial.print(doc["sunrise"].c_str());
// Serial.print(doc["temp"]).c_str();
// Serial.print(doc["humidity"]).c_str();
// doc["cod"] = "forecast";


// docs["sunrise"]         =     doca["city"]["sunrise"];
// docs["sunset"]          =     doca["city"]["sunset"];
// docs["temp"]            =     doca["list"][0]["main"]["temp"];
// docs["feels_like"]      =     doca["list"][0]["main"]["feels_like"];
// docs["temp_min"]        =     doca["list"][0]["main"]["temp_min"];
// docs["temp_max"]        =     doca["list"][0]["main"]["temp_max"];
// docs["humidity"]        =     doca["list"][0]["main"]["humidity"];
// docs["pressure"]        =     doca["list"][0]["main"]["pressure"];
// docs["visibility"]      =     doca["list"][0]["visibility"];
// docs["clouds_all"]      =     doca["list"][0]["clouds"]["all"];
// docs["wind_speed"]      =     doca["list"][0]["wind"]["speed"];         //2.94;
// docs["rain"]            =     doca["list"][0]["rain"]["main"];          //="Rain";
// docs["dt"]              =     doca["list"][0]["dt_txt"];
       
// rain["id"]              =     doca["list"][0]["rain"]["id"];          //=500;
// rain["3h"]              =     doca["list"][0]["rain"]["3h"];          //=0.76;
// rain["icon"]            =     doca["list"][0]["rain"]["icon"];        //"10d";
// rain["description"]     =     doca["list"][0]["rain"]["description"]; //"light rain";






float temp = doc["temp"];
float temp_min = doc["temp_min"];
float temp_max = doc["temp_max"];
float pressure = doc["pressure"];
float humidity = doc["humidity"];
float feels_like = doc["feels_like"];

// Serial.print(temp_min);

                temp_outside_today = temp;
                temp_outside_feels_like_today = feels_like;
                temp_min_today = temp_min;
                temp_max_today = temp_max;
                presure_today =  pressure; // 1033
                humidity_today = humidity; // 84

  if (currentPage == 0)
        {
            updateHomepage();
           
        }

    return 1;
  };

