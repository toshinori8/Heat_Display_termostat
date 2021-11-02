

void updateHomepage()
{

	utft.setColor(80, 110, 50);
	utft.fillRect(0, 100, 220, 181);

	utft.setColor(97, 117, 44);
	utft.fillRect(0, 180, 155, 230);

	uText.setFont(SegoeUISemibold28a);
	int8_t kerning[] = {-4, -4, -4, -4, -100, -8};
	uText.print(110, 97, String(temp_outside_today) + "°C", kerning);
	uText.setFont(SegoeUI13);

	uText.print(5, 100, "MIN ");
	uText.print(55, 100, String(temp_min_today));
	uText.print(5, 120, "MAX ");
	uText.print(55, 120, String(temp_max_today));

	uText.print(20, 185, String(humidity_today) + " hum");
	uText.print(20, 205, String(presure_today) + " Hpa");
}

void displayHomepage()
{

	currentPage = 0;
	utft.clrScr();

	myFiles.load(0, 0, 320, 240, "home.raw", 100, 0);

	utft.setColor(255, 255, 255);
	utft.setBackColor(255, 255, 255);
	uText.setForeground(255, 255, 255);

	//myFiles.load(0, 0, 320, 240, "presure.raw", 100, 0);
writeConfigJson("rooms.json");
	updateHomepage();

};
