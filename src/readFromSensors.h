bool readFromSensors(String jsonMessage)
{

  // Extract Json
  int sta = jsonMessage.indexOf("{");
  int en_ = jsonMessage.indexOf("}");
  String jsonExt = jsonMessage.substring(sta, en_ + 1);

  // Serial.print("------------------");
  // Serial.println(jsonExt);
  // Serial.print("------------------");

  StaticJsonDocument<500> sensorData;

  DeserializationError error = deserializeJson(sensorData, jsonExt);

  if (error)
  {
    Serial.print(F("sensor message failed: "));
    Serial.println(error.c_str());
  }

  // ClearGrass Temp & RH ////  "LYWSD02"
  //  tempc hum id

  if (sensorData.containsKey("tempc"))
  {
    const char *macAddr = sensorData["id"];

    float tempc = sensorData["tempc"];

    updateOnSensor(macAddr, "tempc", tempc);
  }
  if (sensorData.containsKey("hum"))
  {
    const char *macAddr = sensorData["id"];

    int hum = sensorData["hum"];
    updateOnSensor(macAddr, "hum", hum);
  }
  if (sensorData.containsKey("bat"))
  {
    const char *macAddr = sensorData["id"];

    int bat = sensorData["bat"];
    updateOnSensor(macAddr, "bat", bat);
  }



  return true;
}
