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

// typedef struct {
//     int i;
// } test;

// test t[20][20];

///// / ////// / / / /  / /

bool readConfig(){

File dataFile = sd.open("config.json", FILE_READ);
 if (dataFile) {
 
  String config;
  char data;
  // make data to String;
  while ((data = dataFile.read()) >= 0)
  {
   config = config + data;
  }
 
  // close the file:
  dataFile.close();
  Serial.println("option.txt:");
  Serial.println(config);


 }
 else {
  Serial.println("error opening datalog.txt");
  return 0;
 }



}


bool writeConfig(){


String dataString = "{}{}{}{}{} jsonStringin {}{}{}";
 File dataFile = sd.open("config.json", O_WRITE | O_CREAT |O_TRUNC );
 if (dataFile) {
    dataFile.println(dataString);
    dataFile.flush();
    dataFile.close();
 }
 else {
  Serial.println("error opening datalog.txt");
 }
return 1;

}
