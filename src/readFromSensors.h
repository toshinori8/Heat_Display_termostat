bool readFromSensors(String jsonMessage)
{



// Extract Json
int sta= jsonMessage.indexOf("{");
int en_= jsonMessage.indexOf("}");
String jsonExt = jsonMessage.substring(sta,en_+1);

Serial.print("------------------");
Serial.println(jsonExt);
Serial.print("------------------");


StaticJsonDocument<192> sensorData;

DeserializationError error = deserializeJson(sensorData, jsonExt);

if (error) {
  Serial.print(F("sensor message failed: "));
  Serial.println(error.c_str());
  
}

// ClearGrass Temp & RH ////  "LYWSD02"
//  tempc hum id

if (sensorData.containsKey("tempc")) {
  const char* macAddr = sensorData["id"];

  float tempc = sensorData["tempc"];
  updateJsonConfig_sensor(macAddr,"tempc", tempc);
  
}
if (sensorData.containsKey("hum")) {
  const char* macAddr = sensorData["id"];

  int hum = sensorData["hum"];
  updateJsonConfig_sensor(macAddr,"hum", hum);
  
}
if (sensorData.containsKey("bat")) {
  const char* macAddr = sensorData["id"];

  int bat = sensorData["bat"];
  updateJsonConfig_sensor(macAddr,"bat", bat);
  
}




//const char* id = sensorData["id"]; // "58:2D:34:10:D5:EC"
//const char* name = sensorData["name"]; // "ClearGrass Temp & RH"
//int rssi = sensorData["rssi"]; // -92
//const char* model = sensorData["model"]; // "CGG1"
//float temp = sensorData["tempc"]; // 18.8
//float tempf = sensorData["tempf"]; // 65.84
//float hum = sensorData["hum"]; // 58.1






}
