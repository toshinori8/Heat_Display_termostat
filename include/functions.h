int roundfunction(float ax)
{
    ax = ax * 2;
    ax = roundf(ax);
    ax = ax / 2;

    return ax;
}

void updateTimer(int updateInt)
{

    update_timer++;

    if (sleep_state == 0 && update_timer == updateInt)
    {

        if (currentPage == '0')
        {

            Serial1.println("get forecast_5day");
        }
    }
};

    


void drawFrame(int x1, int y1, int x2, int y2)
{
    utft.setColor(255, 0, 0);
    utft.drawRoundRect(x1, y1, x2, y2);
};

void displayWifiIcon(int state)
{

    ///
}

void drawButton(int x1, int y1, int x2, int y2)
{
    utft.setColor(170, 170, 170);
    utft.fillRoundRect(y1 - 3, x1 + 3, y2 - 3, x2 + 3); //Rect Shading

    utft.setColor(255, 255, 255);
    utft.fillRoundRect(y1, x1, y2, x2); //Rect

    utft.setColor(200, 0, 0);
    utft.fillRoundRect(y1 - 5, x1 + 5, y2 + 5, x2 - 5); //inner rect
    return;
}