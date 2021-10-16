#include <Arduino.h>
// #include <SDFat.h>
// SdFat sd;
// ///////// // // // /// //
// typedef struct
// {
//   int temp_set;
//   int temp_actual;
//   int humidity;
//   int heat_state;
// } param_pokoju;

// param_pokoju room[7];


struct pomieszczenie
{

   String name;
   float temp_set;
   float temp_actual;
   float humidity;
   float device;
   bool manage;
   bool heat_state;
};


struct level
{
   String name;
   int id;
   pomieszczenie dane[10];

};

level data[5];

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

void
printFile(const char *filename)
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
   Serial.println();

   // Close the file
   file.close();
}

void readConfigJson(const char *filename)
{
   File file = sd.open(filename);
   StaticJsonDocument<2500> jsonDoc;
   // char JSString = (char)file.read();

   DeserializationError error = deserializeJson(jsonDoc, file);
   if (error)
      Serial.println(F("Failed to read file, using default configuration"));

   Serial.println("// " + jsonDoc["0"]["2"]["name"].as<String>());
   Serial.println("// " + jsonDoc["1"]["4"]["name"].as<String>());

   JsonObject documentRoot = jsonDoc.as<JsonObject>();

    for (JsonPair keyValue : documentRoot)
   {

      Serial.println("key of object");
      Serial.println(keyValue.key().c_str());
      Serial.print("// " + jsonDoc[keyValue.key()]["4"]["name"].as<String>());
   }

   // String output= "";
   //  serializeJson(jsonDoc,output );
   /// Serial.print(output);

   // Serial.print("// "+ jsonDoc["0"]["2"]["name"].as<String>());
   // Serial.print("// "+ jsonDoc["1"]["4"]["name"].as<String>());

   file.close();
   //return jsonDoc;
}
void writeConfigJson(const char *filename, JsonObject &jsonDoc)
{

   String output = "";
   serializeJson(jsonDoc, output);
   Serial.print(output);

   File dataFile = sd.open(filename, O_WRITE | O_CREAT | O_TRUNC);
   if (dataFile)
   {
      dataFile.println(output);
      dataFile.flush();
      dataFile.close();
   }
   else
   {

      Serial.print("Error writing JSON file");
   }
}
