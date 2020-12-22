#include <Arduino.h>
int setupRoom(String roomN)
{

    currentPage = 3;
    utft.clrScr();

    utft.fillScr(116, 137, 54);

    utft.setColor(116, 137, 54);
    utft.fillRect(1, 1, 320, 240);

    myFiles.load(5, 2, 312, 125, "ROOM.RAW", 100, 0);

    uText.setBackground(255,255,255);
    uText.setFont(SegoeUI13);

    if (roomN == "AE")
    {
        uText.print(80, 125, "Sypialnia");
        selectedROOM = 1;
    }
    if (roomN == "W")
    {
        uText.print(80, 125, "Waleria");
        selectedROOM = 2;
    }
    if (roomN == "K")
    {
        uText.print(80, 125, "Kuchania");
        selectedROOM = 3;
    }
    if (roomN == "P")
    {
        uText.print(80, 125, "Przedpokoj");
        selectedROOM = 4;
    }
    if (roomN == "L")
    {
        uText.print(80, 125, "Lazienka");
        selectedROOM = 5;
    }

    if (roomN == "S")
    {
        uText.print(80, 125, "Klatka schodowa");
        selectedROOM = 6;
    }
   myFiles.load(0, 189, 47, 47, "back.raw", 100, 0);
    uText.print(75, 40, String(room[selectedROOM].temp_actual));
    uText.setForeground(100, 100, 110);
    uText.setFont(SegoeUI13);
    uText.print(80, 80, String(room[selectedROOM].temp_set));
    uText.setForeground(100, 100, 110);
    uText.print(150, 80, String(room[selectedROOM].humidity));

    return 1;
}