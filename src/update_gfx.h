#include <Arduino.h>

int update_gfx(int a, int b, int c)
{

    if (currentPage == 0)  //  start page
    { 


    }
    if (currentPage == 1) // displayRooms
    {
    }
    if (currentPage == 3) // SETUP ROOMS piętro
    {
        utft.setColor(243, 244, 245);
        utft.fillRect(64, 12, 176, 108);

        uText.setForeground(100, 100, 110);
        uText.setFont(SegoeUISemibold28a);
        uText.print(75, 40, String(b));
        uText.setForeground(100, 100, 110);
        uText.setFont(SegoeUI13);
        uText.print(80, 80, String(a));
        uText.setForeground(100, 100, 110);
        uText.print(150, 80, String(c));
    }

    return 1;
}