void displayRooms()
{
   lockTouch =true;
    currentPage = 2;


    utft.clrScr();


    utft.setColor(75, 101, 44);
    utft.fillRect(1, 1, 320, 240);
    utft.setColor(210, 210, 210);
    utft.fillRect(58, 1, 319, 239);
           myFiles.load(0, 189, 47, 47, "back.raw", 100, 0);

    //AEWA
    utft.setColor(147, 147, 157);
    utft.drawRect(60, 4, 181, 115);
    utft.drawRect(61, 5, 180, 114);
    utft.drawRect(62, 6, 179, 113);


    uText.setForeground(100, 100, 110);   
    uText.print(75, 20, "SYPIALNIA");

  
    uText.setFont(SegoeUISemibold28a);
    uText.print(75, 40, String(params.level[1].rooms[1].temp_actual,2));
    uText.setForeground(100, 100, 110);
    uText.setFont(SegoeUI13);
    uText.print(80, 80, String(params.level[1].rooms[1].temp_set,2));
    uText.setForeground(100, 100, 110);
    uText.print(150, 80, String(params.level[1].rooms[1].humidity,1));


 // WALERIA
    utft.setColor(147, 147, 157);
    utft.drawRect(60, 117, 181, 236);
    utft.drawRect(61, 118, 180, 235);
    utft.drawRect(62, 119, 179, 234);

    uText.setForeground(100, 100, 110);

    uText.print(200, 20, "WALERIA");

    uText.setFont(SegoeUISemibold28a);
    uText.print(200, 40, String(params.level[1].rooms[2].temp_actual,2));
    uText.setForeground(100, 100, 110);
    uText.setFont(SegoeUI13);
    uText.print(205, 80, String(params.level[1].rooms[2].temp_set,2));
    uText.setForeground(100, 100, 110);
    uText.print(273, 80, String(params.level[1].rooms[2].humidity,1));



    /// KUCHNIA
    utft.setColor(147, 147, 157);
    utft.drawRect(183, 4, 316, 115);
    utft.drawRect(184, 5, 315, 114);
    utft.drawRect(185, 6, 314, 113);

    uText.setForeground(100, 100, 110);

    uText.print(75, 134, "KUCHNIA");

    uText.setFont(SegoeUISemibold28a);

    uText.print(75, 155, String(params.level[1].rooms[0].temp_actual,2));
    uText.setForeground(100, 100, 110);
    uText.setFont(SegoeUI13);
    uText.print(80, 195, String(params.level[1].rooms[0].temp_set,2));
    uText.setForeground(100, 100, 110);
    uText.print(150, 195, String(params.level[1].rooms[0].humidity,1));

    // Przedpokoj
    utft.setColor(147, 147, 157);
    utft.drawRect(183, 117, 240, 236);
    utft.drawRect(184, 118, 239, 235);
    utft.drawRect(185, 119, 238, 234);

    uText.setForeground(100, 100, 110);

    uText.print(190, 150, "");

    uText.setFont(SegoeUI13);
    uText.print(190, 150, String(params.level[1].rooms[4].temp_actual,2));
    uText.setForeground(100, 100, 110);
    uText.print(190, 170, String(params.level[1].rooms[4].temp_set,2));
    uText.setForeground(100, 100, 110);
    uText.print(190, 200, String(params.level[1].rooms[4].humidity,1));

    /// łazienka
    utft.setColor(147, 147, 157);
    utft.drawRect(244, 176, 316, 236);
    utft.drawRect(243, 177, 315, 235);
    utft.drawRect(242, 178, 314, 234);

    uText.setForeground(100, 100, 110);
   // uText.print(250, 180, "Lazienka");
    uText.setFont(SegoeUI13);
    uText.print(250, 180, String(params.level[1].rooms[3].temp_actual,2));
    uText.setForeground(100, 100, 110);
    uText.print(250, 198, String(params.level[1].rooms[3].temp_set,2));
    uText.setForeground(100, 100, 110);
    uText.print(250, 215, String(params.level[1].rooms[3].humidity,1));

    /// schody
    utft.setColor(147, 147, 157);
    utft.drawRect(244, 117, 316, 173);
    utft.drawRect(243, 118, 315, 172);
    utft.drawRect(242, 119, 314, 171);

    uText.setForeground(100, 100, 110);
   // uText.print(250, 128, "Schody");
    uText.setFont(SegoeUI13);
    uText.print(250, 128, String(params.level[1].rooms[5].temp_actual,2));
    uText.setForeground(100, 100, 110);
    uText.print(250, 146, String(params.level[1].rooms[5].temp_set,2));
    uText.setForeground(100, 100, 110);

    // utft.drawBitmap(8, 204, 30, 31, back);

   // Serial.print("lockTouch false");
   //delay(200);

   // delay(1200);
   // lockTouch=false;

      
      touchDelayStart = millis();
      touchDelayRunning = true;



}
