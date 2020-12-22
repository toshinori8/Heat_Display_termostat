#include <Arduino.h>

bool readForecast(String jsonMessage)
{

    Serial.println("readForecast");

    int out = 0;

    if (jsonMessage.indexOf("cod") > 0)
    {

        const size_t capacity = 5 * JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(5) + 15 * JSON_OBJECT_SIZE(1) + 6 * JSON_OBJECT_SIZE(2) + 5 * JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 6 * JSON_OBJECT_SIZE(8) + 5 * JSON_OBJECT_SIZE(9) + 1310;
        DynamicJsonDocument doc(capacity);

        deserializeJson(doc, jsonMessage);

        JsonArray list = doc["list"];
        JsonObject list_0 = list[0]; // list ONE
        JsonObject list_0_main = list_0["main"];

        float list_0_main_temp = list_0_main["temp"];

       double round2(double value) {
   return (int)(value * 100 + 0.5) / 100.0;
}

       Serial.print();



        temp_outside_today = list_0_main["temp"];
        temp_outside_feels_like_today = list_0_main["feels_like"];
        temp_min_today = list_0_main["temp_min"];
        temp_max_today = list_0_main["temp_max"];
        presure_today = list_0_main["pressure"];
        humidity_today = list_0_main["humidity"];

        const char *cod = doc["cod"]; // "200"
        int cnt = doc["cnt"];         // 5

        //temp_outside_today = cod;

        // temp_outside_today      = "12";      // temperatura na zewnątrz.
        // temp_min_today          = "12";      //  najzimniej dzisiaj
        // temp_max_today          = "12";      //  najcieplej dzisiaj
        // presure_today           = "12";      //
        // humidity_today          = "12";      //

        out = 1;
    }
    else
    {
        out = 0;
    }

    return out;
}
