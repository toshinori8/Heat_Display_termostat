#include <Arduino.h>

StaticJsonDocument<4800> jsonDoc;

///// / ////// / / / /  / /

// bool readConfig()
// {

//    File dataFile = sd.open("config.json", FILE_READ);
//    if (dataFile)
//    {

//       String config;
//       char data;
//       // make data to String;
//       while ((data = dataFile.read()) >= 0)
//       {
//          config = config + data;
//       }

//       // close the file:
//       dataFile.close();
//       //   Serial.println("option.txt:");
//       //   Serial.println(config);
//    }
//    else
//    {
//       Serial.println("error opening datalog.txt");
//       return 0;
//    }
// };

// bool writeConfig()
// {

//    String dataString = "{}{}{}{}{} jsonStringin {}{}{}";
//    File dataFile = sd.open("config.json", O_WRITE | O_CREAT | O_TRUNC);
//    if (dataFile)
//    {
//       dataFile.println(dataString);
//       dataFile.flush();
//       dataFile.close();
//    }
//    else
//    {
//       Serial.println("error opening datalog.txt");
//    }
//    return 1;
// }

void printFile(const char *filename)
{
   // Open file for reading
   File file = sd.open(filename);
   if (!file)
   {
      Serial.println(F("Failed to read file"));
      return;
   }

   // Extract each characters by one by one
   while (file.available())
   {
      Serial.print((char)file.read());
   }

   // Close the file
   file.close();
}

void readConfigJson(const char *filename)
{

   File file = sd.open(filename);

   DeserializationError error = deserializeJson(jsonDoc, file);
   if (error)
   {
      Serial.println(F("Failed to read file"));
   }

   int sLevel = sizeof(params.level) / sizeof(params.level[0]);

   if (sLevel)
   {

      Serial.println(F("Previus state loaded"));
   }

   for (uint8_t i = 0; i < sLevel; ++i)
   {

      String sI = String(i);

      //Serial.println("level :" + String(i) + " Level from Json : " + jsonDoc[sI]["levelName"].as<String>());

      params.level[i].name = jsonDoc[sI]["name"].as<String>();
      params.level[i].used = jsonDoc[sI]["used"].as<bool>();
      params.level[i].id = jsonDoc[sI]["id"].as<int>();

      if (jsonDoc[sI].containsKey("conf"))
      {
         Serial.write("Znaleziono konfugurację whitelist");

         Serial.println(jsonDoc[sI]["conf"]["whiteList"]["1"].as<String>());

         JsonObject _whiteList = jsonDoc[sI]["conf"]["whiteList"].as<JsonObject>();

         for (JsonPair el : _whiteList)
         {

            Serial.println(el.key().c_str());
            Serial.println(el.value().as<char *>());
            WhiteList += "\"" + el.value().as<String>() + "\",";
         }

         WhiteList = WhiteList.substring(0, WhiteList.length() - 1);
      };

      Serial.print(WhiteList);

      int sRoom = sizeof(params.level[i].rooms) / sizeof(params.level[i].rooms[0]);
      for (uint8_t g = 0; g < sRoom; ++g)
      {
         String Sg = String(g);
         //  Serial.println("room #: " + Sg +" - "+ jsonDoc[sI][Sg]["name"].as<String>()+ "  "+ jsonDoc[sI][Sg]["temp_set"].as<String>());

         params.level[i].rooms[g].id = jsonDoc[sI][Sg]["id"].as<int>();
         params.level[i].rooms[g].used = jsonDoc[sI][Sg]["used"].as<int>();
         params.level[i].rooms[g].name = jsonDoc[sI][Sg]["name"].as<String>();
         params.level[i].rooms[g].temp_set = jsonDoc[sI][Sg]["temp_set"].as<float>();
         params.level[i].rooms[g].temp_actual = jsonDoc[sI][Sg]["temp_actual"].as<float>();
         params.level[i].rooms[g].humidity = jsonDoc[sI][Sg]["humidity"].as<int>();
         params.level[i].rooms[g].heat_state = jsonDoc[sI][Sg]["heat_state"].as<bool>();
         params.level[i].rooms[g].device = jsonDoc[sI][Sg]["device"].as<String>();
         params.level[i].rooms[g].valve = jsonDoc[sI][Sg]["valve"].as<String>();
         params.level[i].rooms[g].manage = jsonDoc[sI][Sg]["manage"].as<bool>();
      }
   }

   JsonObject documentRoot = jsonDoc.as<JsonObject>();

   for (JsonPair keyValue : documentRoot)
   {
      // Serial.println("key of object");
      // Serial.println(keyValue.key().c_str());
      // Serial.print("// " + jsonDoc[keyValue.key()]["4"]["name"].as<String>());
   }

   file.close();
}
void writeConfigJson(const char *filename)
{
   /////////////////////////////////////

   int sLevel = sizeof(params.level) / sizeof(params.level[0]);

   for (uint8_t i = 0; i < sLevel; ++i)
   {
      String sI = String(i);
      int sRoom = sizeof(params.level[i].rooms) / sizeof(params.level[i].rooms[0]);
      for (uint8_t g = 0; g < sRoom; ++g)
      {
         String Sg = String(g);
         jsonDoc[sI][Sg]["id"] = params.level[i].rooms[g].id;
         jsonDoc[sI][Sg]["used"] = params.level[i].rooms[g].used;
         jsonDoc[sI][Sg]["name"] = params.level[i].rooms[g].name.c_str();
         jsonDoc[sI][Sg]["temp_set"] = params.level[i].rooms[g].temp_set;
         jsonDoc[sI][Sg]["temp_actual"] = params.level[i].rooms[g].temp_actual;
         jsonDoc[sI][Sg]["humidity"] = params.level[i].rooms[g].humidity;
         jsonDoc[sI][Sg]["heat_state"] = params.level[i].rooms[g].heat_state;
         jsonDoc[sI][Sg]["device"] = params.level[i].rooms[g].device.c_str();
         jsonDoc[sI][Sg]["valve"] = params.level[i].rooms[g].valve.c_str();
         jsonDoc[sI][Sg]["manage"] = params.level[i].rooms[g].manage;
      }
   }

   String parrams = "";

   serializeJson(jsonDoc, parrams);

   //Serial.println(parrams);

   //////////////////////////
   File dataFile = sd.open(filename, O_WRITE | O_CREAT | O_TRUNC);
   if (dataFile)
   {
      dataFile.println(parrams);
      dataFile.flush();
      dataFile.close();
   }
   else
   {

      Serial.print("Error writing JSON file");
   }
}

void updateOnSensor(String device, String dataTy, float value)
{
 

   int sLevel = sizeof(params.level) / sizeof(params.level[0]);

   for (uint8_t i = 0; i < sLevel; ++i)
   {

      String sI = String(i);
      int sRoom = sizeof(params.level[i].rooms) / sizeof(params.level[i].rooms[0]);
      
      
      

      for (uint8_t g = 0; g < sRoom; ++g)
      {
         String Sg = String(g);

         if (params.level[1].rooms[g].device == device)
         {


            Serial.println("Updating "+dataTy+ " : " + String(params.level[i].rooms[g].name));
            Serial.println("Device attached :" + String(params.level[i].rooms[g].device));


            if (dataTy == "tempc")
            {

               jsonDoc[sI][Sg]["temp_actual"] = value;
               params.level[i].rooms[g].temp_actual = value;

               /// Update heat_state:
               if (params.level[i].rooms[g].temp_set > params.level[i].rooms[g].temp_actual)
               {
                  params.level[1].rooms[selectedROOM].heat_state = 1;
                  //jsonDoc[sI][Sg]["heat_state"] = 1;
                  //turnValve("1", String(jsonDoc[sI][Sg]["valve"]), "ON");
               }
               else
               {
                  //jsonDoc[sI][Sg]["heat_state"] = 0;
                  params.level[1].rooms[selectedROOM].heat_state = 0;
                  //turnValve("1", String(jsonDoc[sI][Sg]["valve"]), "OFF");
               }
            }
            if (dataTy == "hum")
            {
               jsonDoc[sI][Sg]["humidity"] = value;
               //params.level[i].rooms[g].humidity = value;
            }
            //Serial.println(params.level[i].rooms[g].name);
            //  Serial.println("________________________________");
         };

         // jsonDoc[sI][Sg]["id"]               = params.level[i].rooms[g].id;
         // jsonDoc[sI][Sg]["used"]             = params.level[i].rooms[g].used;
         // jsonDoc[sI][Sg]["name"]             = params.level[i].rooms[g].name.c_str();
         // jsonDoc[sI][Sg]["temp_set"]         = params.level[i].rooms[g].temp_set;
         // jsonDoc[sI][Sg]["temp_actual"]      = params.level[i].rooms[g].temp_actual;
         // jsonDoc[sI][Sg]["humidity"]         = params.level[i].rooms[g].humidity;
         // jsonDoc[sI][Sg]["heat_state"]       = params.level[i].rooms[g].heat_state;
         // jsonDoc[sI][Sg]["device"]           = params.level[i].rooms[g].device.c_str();
         // jsonDoc[sI][Sg]["manage"]           = params.level[i].rooms[g].manage;
      }
   }

   if (currentPage == 2)
   {
      checkHeatState();
      displayRooms();
   }
   if (currentPage == 1)
   {
      checkHeatState();
   }
}

bool checkHeatState()
{

   
   bool HeatState = 0;

   int sLevel = sizeof(params.level) / sizeof(params.level[0]);
   for (uint8_t i = 0; i < sLevel; ++i)
   {
      String sI = String(i);
      int sRoom = sizeof(params.level[i].rooms) / sizeof(params.level[i].rooms[0]);
      for (uint8_t g = 0; g < sRoom; ++g)
      {
         String Sg = String(g);

      Serial.println("HeatState ["+ String(params.level[i].rooms[g].heat_state)+"] for room "+ String(params.level[i].rooms[g].name));

         if (String(params.level[i].rooms[g].heat_state) == "1")
         {

            HeatState = 1;
         }
         else
         {

            HeatState = 0;
         }
      }
   }

   if (currentPage == 0)
   {

      if (String(HeatState) == "1")
      {
         myFiles.load(258, 184, 55, 56, "heat_state_on.raw", 100, 0);
      }
      else if (String(HeatState) == "0")
      {
         myFiles.load(258, 184, 55, 56, "heat_state_off.raw", 100, 0);
      }
   }

   return HeatState;
}