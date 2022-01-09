#include <Arduino.h>
#include <ArduinoJson.h>
#include <UTFT.h>
#include <URTouch.h>
#include <uText.h>
#include <SPI.h>
#include <SDFat.h>
#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;
#include <UTFT_SdRaw.h>
#include "math.h"
// #include <arduino-timer.h>
const int ON_TIME = 300;
const int OFF_TIME = 1000;
// file system object
SdFat sd;

String WhiteList = "";
// class Devices {
// public: struct WhiteList{
//       int id;
//       String mac;
//   } whitelist[8];
// };

class roomParams
{
public:
  struct Rooms
  {
    String name;
    int id;
    bool used;
    float temp_set;
    float temp_actual;
    int humidity;
    String device;   // MAC ADDR
    String valve;    // # valve przypoprządkowany do pokoju
    bool manage;     // czy pokj ma być zarządzany - ustawiane w aplikacji  WEB
    bool heat_state; // Aktualny stan grzania.
  } rooms[6];

public:
  struct level
  {
    int id;
    bool used;
    String name;
    Rooms rooms[7];
  } level[3];
};

//Devices devices;   // urądzenia mierzące temperaturę.
roomParams params; // parametry pokoi   ------------  level / room / attributes

///auto timer = timer_create_default();

//ArduinoOutStream cout(Serial);
// Sd2Card sd;
// SdVolume volume;
// SdFile root;


unsigned long prevMillisTouch = 0; // track time between touches
unsigned long prevMillis5sec = 0;  // track 5 seconds for refreshing clock and temp
unsigned long feedingMillis = 0;   // track how long we've been feeding
unsigned long millisDim = 0;       // used for brightness adjustment
unsigned long millisHome = 0;      // used for returning home after configured time

int x, y;
int currentPage;
int bootup;
int selectedROOM;
#define null NULL
#define SD_CHIP_SELECT 42 // SD chip select pin
#define SPI_SPEED SD_SCK_MHZ(4)
File configFile;
// #define ESP8266 Serial1; // Serial 9600

int updateInt = 550000; //miliseconds
unsigned long previousMillis = 0;
int update_timer;
int sleep_timer = 0; // 1000
int sleep_state = 0;
int sleep_time = 90000000; // ustawić na 1000000

int is_back = 0;
String option;
String input;
String jsonInput;
int CH_PD_8266 = 50; // High gdy normalna praca
int RST_ESP = 44;    // Reset PIN musi być na HIGH ponieważ nie ma podwieszenia do VCC
int VCC_lcd = 15;    // Pin 15 zasilanie LCD

int ready = 0;

float hysterizRoom = 0.25;

float temp_outside_today = 15;           // temperatura na zewnątrz.
float temp_outside_feels_like_today = 0; // temperatura na zewnątrz odczuwalna
float temp_min_today = 0;                //  najzimniej dzisiaj
float temp_max_today = 0;                //  najcieplej dzisiaj
float presure_today = 0;                 //  cisnienie baryczne aktualne
float humidity_today = 0;                //  wilgotność aktualna

const char *temp_outside_today_01 = "16"; // temperatura na zewnątrz.
const char *temp_min_today_01 = "0";      //  najzimniej dzisiaj
const char *temp_max_today_01 = "0";      //  najcieplej dzisiaj
const char *presure_today_01 = "0";       //  cisnienie baryczne aktualne
const char *humidity_today_01 = "0";      //  wilgotność aktualna

const char *temp_outside_today_02 = "17"; // temperatura na zewnątrz.
const char *temp_min_today_02 = "0";      //  najzimniej dzisiaj
const char *temp_max_today_02 = "0";      //  najcieplej dzisiaj
const char *presure_today_02 = "0";       //  cisnienie baryczne aktualne
const char *humidity_today_02 = "0";      //  wilgotność aktualna

UTFT utft(ILI9341_16, 38, 39, 40, 41);
uText uText(&utft, 320, 240);
URTouch myTouch(6, 5, 4, 3, 2);

UTFT_SdRaw myFiles(&utft);

const int8_t DISABLE_CHIP_SELECT = 10;

extern prog_uint16_t img_presure[494] PROGMEM;
extern prog_uint16_t img_hum[494] PROGMEM;
extern prog_uchar SegoeUI13[1855] PROGMEM;
extern prog_uchar SegoeUISemibold28a[10780] PROGMEM;

unsigned long touchDelayStart = 0; // touch delay
bool touchDelayRunning = false;

void displayHomepage();
bool readConfig();
bool writeConfig();
void displayRooms();
bool readForecast(String jsonMessage);
bool readFromSensors(String jsonMessage);
void readConfigJson(const char *filename);
void writeConfigJson(const char *filename);
bool turnValve(String level, String valve, String state);

void drawFrame(int x1, int y1, int x2, int y2);
void displayWifiIcon(int state);

bool checkHeatState();

int setupRoom(String roomN);

int update_gfx(float a, float b, int c);
int roundfunction(float);

bool sendWhitelist();

int myX = 200;
int myY = 20;

bool lockTouch = true;

String roomsJson = "";

void setup()
{

  bootup = 1;
  currentPage = 0; // aktualna strona

  Serial.begin(9600);
  Serial1.begin(9600);

  utft.InitLCD(LANDSCAPE);
  pinMode(VCC_lcd, OUTPUT);
  pinMode(CH_PD_8266, OUTPUT);
  
  

  digitalWrite(RST_ESP, HIGH);
  digitalWrite(CH_PD_8266, HIGH); // +3.3V  PIN 50 ESP TURN ON
  digitalWrite(VCC_lcd, 65);      // +5V PIN 15 - DISPLAY TURN ON

  utft.clrScr();

  utft.setColor(255, 255, 255);
  utft.setBackColor(0, 0, 0);
  uText.setBackground(0, 0, 0);
  uText.setFont(SegoeUI13);
  uText.print(200, 20, "Wczytuje dane..");

  bool mysd = 0;
  while (!mysd)
  {
    delay(300);
    if (!sd.begin(SD_CHIP_SELECT, SD_SCK_MHZ(41)))
    {

      Serial.println(F("Card failed, or not present"));
      Serial.println(F("Retrying...."));
    }
    else
    {
      mysd = 1;
      myFiles.load(0, 0, 320, 240, "LOGOCOM.RAW", 100, 0);
      Serial.println(F("Card initialised."));

      readConfigJson("rooms.json");
      
    }
  }

  utft.setColor(255, 255, 255);
  utft.fillRect(100, 0, 319, 29);
  utft.setColor(100, 100, 100);
  utft.setBackColor(100, 100, 100);
  uText.setForeground(100, 100, 100);
  
  
  uText.print(myX, myY, "WiFi");
  
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_EXTREME);
  displayHomepage();
}

void loop()
{

  unsigned long currentMillis = millis(); // get current millis

  sleep_timer++;
  if (sleep_state == 0 && sleep_timer == sleep_time)
  {
    sleep_timer = 0;            // reseting sleeptimer
    sleep_state = 1;            // setting sleep state to ON
    digitalWrite(VCC_lcd, LOW); // turning OFF display
  }
  if (myTouch.dataAvailable() && sleep_state == 1)
  {
    digitalWrite(VCC_lcd, HIGH); // TURN DISPLAY ON
    sleep_timer = 0;             //
    sleep_state = 0;
  }

  String message = "";
  while (Serial1.available() > 0)
  {
    message = Serial1.readString();
    delay(200);
    if (message.indexOf("wifi") > 0)
    {
      Serial.println("Wifi Connected");
      if (bootup == 1)
      {
        Serial1.println("get forecast_5h");
      }
    }
    if (message.indexOf("cod\":\"forecast") > 0)
    {
      if (bootup == 1)
      {
        Serial.println("Connecting MQTT server...");
        Serial1.println("mqttserver 192.168.8.150");
      }
      else
      {
        readForecast(message);
      };
    }
    if (message.indexOf("mqtt connected") > 0)
    {
      Serial.println("Connected to MQTTGateway");
      Serial.println("Sening MQQT config...");

      sendWhitelist();

      delay(5000);
      Serial.println("Adding Subscription... home/MQTTGateway/BTtoMQTT/#");

      Serial1.println("subscribe home/MQTTGateway/BTtoMQTT/#");
    }
    if (message.indexOf("mqtt not connected") > 0)
    {
      // Serial.println("[mqtt not connected]");
    }
    if (message.indexOf("subscription added") > 0)
    {
      Serial.println("[subscription added] Listening in readFromSensors");

      bootup = 0;
    }

    if (message.indexOf("home/MQTTGateway/BTtoMQTT") > 0)
    {

      readFromSensors(message);
    }

    else
    {
      // print raw message

      // Serial.println("RAW MESSAGE: " + message);
    }
  }
  while (Serial.available() > 0)
  {
    char d = Serial.read();
    Serial1.write(d);
  }

  // TOUCH DELAY
  if (touchDelayRunning && ((millis() - touchDelayStart) >= 2 * 500))
  {
    touchDelayRunning = false; // finished delay -- single shot, once only
    lockTouch = false;         // turn led off
    // Serial.println("Touch przywrocony ");
  }
  if (currentMillis - previousMillis >= 40 * 10000)
  {
    previousMillis = currentMillis;
  }

  if (currentMillis - prevMillisTouch > 300) // make sure it's been .5 sec between touches
  {

    prevMillisTouch = currentMillis; // reset the touch timer
    millisDim = currentMillis;       // reset screen dim timer
    millisHome = currentMillis;      // reset return home timer

#include <touchSetup.h>
  }
}

// |RESOURCES
//#include <resources.h>
#include <img_fonts.h>
//#include <img_controls.h>
//#include <img_arduino_logo.h>
//#include <img_setupROOM.h>

// APP CODE
#include <readConfig.h>
#include <update_gfx.h>
#include <displayHomepage.h>
#include <displayRooms.h>
#include <setupRoom.h>
#include <readForecast.h>
#include <functions.h>
#include <readFromSensors.h>
#include <valveControl.h>
