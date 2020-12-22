
bool readFromSensors()
{
///
int responns = 0;
// Serial.println("Connectig to temperature Sensors");
// Serial1.println("get bluetooth data");
// Serial.println("get bluetooth data");

/// get data and set array 

  Serial.println("readFromSensors");

///  AE
    room[1].temp_set = 1;
    room[1].temp_actual = 1;
    room[1].humidity = 1;
///  Waleria
    room[2].temp_set = 2;
    room[2].temp_actual = 2;
    room[2].humidity = 2;
///  Kuchnia
    room[3].temp_set = 3;
    room[3].temp_actual = 3;
    room[3].humidity = 3;
///  Łazienka
    room[4].temp_set = 4;
    room[4].temp_actual = 4;
    room[4].humidity = 4;
///  Przedpokój
    room[5].temp_set = 5;
    room[5].temp_actual = 5;
    room[5].humidity = 5;
///  Klatka schodowa
    room[6].temp_set = 6;
    room[6].temp_actual = 6;
    room[6].humidity = 6;
    //room[2] = record_type{1,2};


 
 // param_pokoju configurationFromFlash; // create a temporary struct
  
  





           


responns = 1;


    return responns;
}
