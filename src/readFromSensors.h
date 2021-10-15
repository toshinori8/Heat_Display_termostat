bool readFromSensors(String jsonMessage)
{
///
int responns = 0;

/// get data and set array 

///  AE
    level[0]room[1].temp_set = 1;
    level[0]room[1].temp_actual = 1;
    level[0]room[1].humidity = 1;
///  Waleria
    level[0]room[2].temp_set = 2;
    level[0]room[2].temp_actual = 2;
    level[0]room[2].humidity = 2;
///  Kuchnia
    level[0]room[3].temp_set = 3;
    level[0]room[3].temp_actual = 3;
    level[0]room[3].humidity = 3;
///  Łazienka
    level[0]room[4].temp_set = 4;
    level[0]room[4].temp_actual = 4;
    level[0]room[4].humidity = 4;
///  Przedpokój
    level[0]room[5].temp_set = 5;
    level[0]room[5].temp_actual = 5;
    level[0]room[5].humidity = 5;
///  Klatka schodowa
    level[0]room[6].temp_set = 6;
    level[0]room[6].temp_actual = 6;
    level[0]room[6].humidity = 6;
    //room[2] = record_type{1,2};
 // param_pokoju configurationFromFlash; // create a temporary struct
  
        // if (jsonMessage.indexOf("sensors") > 0){

        //     DynamicJsonDocument doc(400);

        //     deserializeJson(doc,jsonMessage);
        
        
        
        
        // }
    

responns = 1;
    return responns;
}
