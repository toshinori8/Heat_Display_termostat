if (myTouch.dataAvailable())
{

    sleep_timer = 0;
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();

    if (currentPage == 0) // display Home Screen
    {

        // update forecast icon img_forecast_gif
        if ((x >= 259) && (x <= 311) && (y >= 74) && (y <= 118))
        {
            //drawFrame(59, 74, 311, 118);
            Serial1.println("get forecast_5h");
            // Serial.println("touch -> get forecast_5h");
        }
        //  getRooms Button / shows room in house
        if ((x >= 259) && (x <= 311) && (y >= 118) && (y <= 164))
        {
            currentPage = 2;
            displayRooms();
        }
    }
    if (currentPage == 2 && lockTouch==false) // display Rooms
    {
        // Back Button
        if ((x >= 2) && (x <= 54) && (y >= 170) && (y <= 240))
        {
            drawFrame(2, 200, 54, 240);
            delay(500);
            displayHomepage();
        }
        // touch AE room   64, 8, 178, 114
        if ((x >= 64) && (x <= 177) && (y >= 8) && (y <= 112))
        {
            drawFrame(64, 8, 177, 112);
            delay(500);
            setupRoom("AE");
        }
        // touch Waleria room   188, 6, 313, 114
        if ((x >= 188) && (x <= 313) && (y >= 8) && (y <= 112))
        {
            drawFrame(188, 8, 313, 112);
            delay(500);
            setupRoom("W");
        }
        // touch kuchnia  65, 123, 177, 235
        if ((x >= 64) && (x <= 177) && (y >= 120) && (y <= 234))
        {
            drawFrame(64, 120, 177, 234);
            delay(500);
            setupRoom("K");
        }
        // touch przedpokoj  190, 120, 236, 233
        if ((x >= 187) && (x <= 237) && (y >= 120) && (y <= 234))
        {
            drawFrame(187, 121, 237, 234);
            delay(500);
            setupRoom("P");
        }
        // touch łazienka  245, 179, 314, 235
        if ((x >= 247) && (x <= 315) && (y >= 180) && (y <= 234))
        {
            drawFrame(247, 180, 315, 234);
            delay(500);
            setupRoom("L");
        }
        // touch klatka schodowa  245, 179, 314, 235
        if ((x >= 247) && (x <= 315) && (y >= 120) && (y <= 170))
        {
            drawFrame(247, 120, 315, 170);
            delay(500);
            setupRoom("S");
        }
    }
    if (currentPage == 3) // setup Rooms
    {
        // Back Button
        if ((x >= 2) && (x <= 54) && (y >= 170) && (y <= 240))
        {
            if (configFile.available())
            {
                configFile.read((uint8_t *)&room, sizeof(room));
            }
            displayRooms();
        }
        // BUTTON UP 185, 8, 316, 53
        if ((x >= 190) && (x <= 313) && (y >= 0) && (y <= 53))
        {
            room[selectedROOM].temp_set = room[selectedROOM].temp_set + 1;
            //Serial.println(String(room[selectedROOM].temp_set));
            update_gfx(
                room[selectedROOM].temp_set,
                room[selectedROOM].temp_actual,
                room[selectedROOM].humidity);
        }

        // BUTTON DOWN 188, 63, 314, 109
        if ((x >= 190) && (x <= 313) && (y >= 60) && (y <= 100))
        {
            room[selectedROOM].temp_set = room[selectedROOM].temp_set - 1;
            update_gfx(
                room[selectedROOM].temp_set,
                room[selectedROOM].temp_actual,
                room[selectedROOM].humidity);
        }
    }


}