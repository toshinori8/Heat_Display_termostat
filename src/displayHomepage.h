
void displayHomepage()
{


	currentPage = 0;
	utft.clrScr();

	myFiles.load(0, 0, 320, 240, "home.raw", 100, 0);

	utft.setColor(255, 255, 255);
	utft.setBackColor(255, 255, 255);
	uText.setForeground(255, 255, 255);

	uText.setFont(SegoeUISemibold28a);

	int8_t kerning[] = {-4, -4, -4, -4, -100, -8};
	uText.print(100, 111, String(temp_outside_today) + "°C", kerning);

	uText.setFont(SegoeUI13);

	uText.print(10, 110, "MIN");
	uText.print(40, 110, String(temp_min_today));
	uText.print(10, 130, "MAX");
	uText.print(40, 130, String(temp_max_today));

	uText.print(40, 170, String(humidity_today) + " %");
	uText.print(115, 170, String(presure_today) + " Hpa");
};