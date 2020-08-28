//SuR (ESP-12E module) NTP & RTC Clock
//24h only screen, russian week day, 32x16 matrix with two zones

//WiFi AP & EEPROM https://github.com/techiesms/WiFi-Credentials-Saving---Connecting
#include <MD_Parola.h>
#include <MD_MAX72xx.h> //https://github.com/MajicDesigns/MD_MAX72XX
#include <SPI.h>
#include "font_clock.h"
#include <Rtc_Pcf8563.h> //https://github.com/elpaso/Rtc_Pcf8563
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <NTPClient.h> //https://github.com/arduino-libraries/NTPClient
#include <WiFiUdp.h>
#include "DHT.h"
#include <EEPROM.h>

uint8_t wd = 0;
uint8_t dd = 0;
uint8_t mm = 0;
uint16_t yy = 2020;
uint8_t h = 0;
uint8_t m = 0;
uint8_t s = 0;
String newStr = "";
String lastNTPcheck = "Newer :(";
bool dht_T_flag = false;
bool dht_H_flag = false;
bool ntp_get = false;
uint8_t BrightnessUp = 4;
uint8_t BrightnessLo = 2;
uint8_t FontUpNum = 2;
uint8_t FontUpNumMax = 3; //available fonts
bool wifi_ok = false;

#define PRINTS(s) Serial.print(F(s));
#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

#define NUM_ZONES 2
#define ZONE_SIZE 4
#define MAX_DEVICES (NUM_ZONES * ZONE_SIZE)
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define ZONE_UPPER  0
#define ZONE_LOWER  1

#define ONE_HRS 3600000UL
#define HALF_HRS 1800000UL

// need to be adapted
#define CLK_PIN   D5 // or SCK
#define DATA_PIN  D7 // or MOSI
#define CS_PIN    D8 // or SS
//clock pins (grey)SCK(SCL) - (gpio5)D1, (violet)SDA - (gpio4)D2
#define DHT_PIN   D3
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define PIN_PHOTO_SENSOR A0
//#define PIN_TONE D6

DHT dht(DHT_PIN, DHTTYPE);
Rtc_Pcf8563 RTC;
//MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "RU.pool.ntp.org", 3600, 60000);
ESP8266WebServer server(80);

//const int led = BUILTIN_LED; //gpio16, gpio2 (setup in Tools Arduino IDE)
const char *ssid     = "xxxxxxxx";
const char *password = "yyyyyyyy";
const float timeZone = 3.0; //Europe/Moscow

#define SPEED_TIME_LOWER 50 // speed of the transition
#define SPEED_TIME_UPPER 15
#define PAUSE_TIME  2000

#define MAX_MESG  21
char szMesg[MAX_MESG] = {""};
char szTime[MAX_MESG] = {""};
char szMesgNew[MAX_MESG] = {""}; //{"00 00.00"};
char szTimeNew[MAX_MESG] = {""}; //{"00:00"};

void ReadBrightness ()
{
  BrightnessUp = uint8_t(EEPROM.read(100));
  if (BrightnessUp > 15) BrightnessUp = 5;
  BrightnessLo = uint8_t(EEPROM.read(101));
  if (BrightnessLo > 15) BrightnessLo = 5;
}

void WriteBrightness ()
{
  EEPROM.write(100, BrightnessUp);
  EEPROM.write(101, BrightnessLo);
  EEPROM.commit();
}

void ReadFontUpNum ()
{
  FontUpNum = uint8_t(EEPROM.read(102));
  if (FontUpNum > FontUpNumMax) FontUpNum = 2;
}

void WriteFontUpNum ()
{
  EEPROM.write(102, FontUpNum);
  EEPROM.commit();
}
void getTime(char *psz, bool f = true)
{
  s = RTC.getSecond();
  m = RTC.getMinute();
  h = RTC.getHour(); //24hr Format
  sprintf(psz, "%02d%c%02d", h, (f ? ':' : ' '), m);
  //strcpy(szTimeNew, "00:00");
}

void SetFontUpNum()
{
  switch ( FontUpNum )
  {
    case 1:
    default:
      P.setFont(ZONE_UPPER, NumFontUpper);
      break;

    case 2:
      P.setFont(ZONE_UPPER, NumFontUpperThin);
      break;

    case 3:
      P.setFont(ZONE_UPPER, NumFontUpperBold);
      break;
  }
}

void getDate(char *psz)
{
  dd = RTC.getDay();
  mm = RTC.getMonth();
  //  yy = RTC.getYear();
  if ( ntp_get ) {
    //show ntp update icon
    wd = 8;
    dht_T_flag = false;
    dht_H_flag = false;
    ntp_get = false;
  } else {
    wd = RTC.getWeekday();
  }
  if (dht_T_flag) {
    sprintf(psz, "%02d!%02d/%02d", (int)dht.readTemperature(), dd, mm);
  } else if (dht_H_flag) {
    sprintf(psz, "%02d%s%02d/%02d", (int)dht.readHumidity(), "%", dd, mm);
  } else {
    sprintf(psz, "%c%c%02d/%02d", wd + 60, (wifi_ok ? '.' : ' '), dd, mm);
  }
  //strcpy(szMesgNew, "00 00.00");
}

void timeCheck() {

  timeClient.update();

  h = timeClient.getHours();
  //String hoursStr = h < 10 ? "0" + String(h) : String(h);
  m = timeClient.getMinutes();
  s = timeClient.getSeconds();
  wd = timeClient.getDay();
  wd =  wd == 0 ? 7 : wd ;

  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);
  yy = ti->tm_year + 1900;
  mm = ti->tm_mon + 1;
  dd = ti->tm_mday;
  //   uint8_t hours = ti->tm_hour;
  //   uint8_t minutes = ti->tm_min;
  //   uint8_t seconds = ti->tm_sec;

  String yearStr = String(yy);
  String monthStr = mm < 10 ? "0" + String(mm) : String(mm);
  String dayStr = dd < 10 ? "0" + String(dd) : String(dd);
  String weekdayStr = String(wd);
  String hoursStr = h < 10 ? "0" + String(h) : String(h);
  String minuteStr = m < 10 ? "0" + String(m) : String(m);
  String secondStr = s < 10 ? "0" + String(s) : String(s);

  String timeStr = dayStr + "-" + monthStr + "-" + yearStr + " " +
                   hoursStr + ":" + minuteStr + ":" + secondStr + " week day: " + weekdayStr;

  PRINT("\nNTP time > ", timeStr);
  //dataStr = timeClient.getFormattedTime();
  //PRINT("\nNTP formatted > ", dataStr);

  if ( yy != 1970 )
  {
    //set a time from NTP
    //day, weekday, month, century(1=1900, 0=2000), year(0-99)
    RTC.setDate(dd, wd, mm, 0, yy - 2000);
    //hr, min, sec
    RTC.setTime(h, m, s);

    //    newStr = "Get NTP time Ok.";
    //    P.displayClear(ZONE_UPPER);
    //    newStr.toCharArray(szTime, MAX_MESG);
    //    P.displayZoneText(ZONE_UPPER, szTime, PA_CENTER, SPEED_TIME_UPPER, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);

    lastNTPcheck = DateTimeStr();
  }
}

String ip2Str(IPAddress ip) {
  String s = "";
  for (int i = 0; i < 4; i++) {
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  }
  return s;
}

String DateTimeStr() {
  return  String(dd) + "/" + String(mm) + "/" + String((RTC.getYear() + 2000)) + " (" + String(wd) + ") " + String(h) + ":" + String(m) + ":" + String(s);
}

void PrintIP()
{
  // scroll local IP in ZONE_LOWER
  newStr = ip2Str(WiFi.localIP());
  PRINT("\nWiFi Local IP > ", newStr);
  newStr.toCharArray(szMesg, MAX_MESG); //newStr.length() + 1);
  P.displayClear(ZONE_LOWER);
  P.displayReset(ZONE_LOWER);
  P.setTextEffect(ZONE_LOWER, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

String SendHTML(float TempCstat, float Humiditystat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  //ptr +="<meta http-equiv=\"refresh\" content=\"2\">\n";
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";

  ptr += "<title>SuR Clock Report</title>\n";

  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += ".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr += ".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  ptr += ".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr += ".humidity{font-weight: 300;font-size: 50px;color: #3498db;}\n";
  ptr += ".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  ptr += ".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr += ".temperature{font-weight: 300;font-size: 50px;color: #f39c12;}\n";
  ptr += ".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr += ".data{padding: 10px;}\n";
  ptr += "</style>\n";

  //  ptr += "<script>\n";
  //  ptr += "setInterval(loadDoc,200);\n";
  //  ptr += "function loadDoc() {\n";
  //  ptr += "var xhttp = new XMLHttpRequest();\n";
  //  ptr += "xhttp.onreadystatechange = function() {\n";
  //  ptr += "if (this.readyState == 4 && this.status == 200) {\n";
  //  ptr += "document.getElementById(\"webpage\").innerHTML =this.responseText}\n";
  //  ptr += "};\n";
  //  ptr += "xhttp.open(\"GET\", \"/\", true);\n";
  //  ptr += "xhttp.send();\n";
  //  ptr += "}\n";
  //  ptr += "</script>\n";

  ptr += "</head>\n";
  ptr += "<body>\n";

  ptr += "<div id=\"webpage\">\n";

  ptr += "<h1>SuR Clock</h1>\n";
  ptr += "<h3>" + DateTimeStr() + "</h3>\n";
  ptr += "Last NTP check: " + lastNTPcheck + "\n";

  ptr += "<div class=\"data\">\n";

  ptr += "<div class=\"side-by-side temperature-icon\">\n";
  ptr += "<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
  ptr += "width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";

  ptr += "<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
  ptr += "c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
  ptr += "c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
  ptr += "c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
  ptr += "c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"></path>\n";

  ptr += "</svg>\n";
  ptr += "</div>\n";

  ptr += "<div class=\"side-by-side temperature-text\">Temperature</div>\n";
  ptr += "<div class=\"side-by-side temperature\">";
  ptr += (int)TempCstat;
  ptr += "<span class=\"superscript\">C</span></div>\n";
  ptr += "</div>\n";

  ptr += "<div class=\"data\">\n";
  ptr += "<div class=\"side-by-side humidity-icon\">\n";
  ptr += "<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";

  ptr += "<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
  ptr += "c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";

  ptr += "</svg>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"side-by-side humidity-text\">Humidity</div>\n";
  ptr += "<div class=\"side-by-side humidity\">";
  ptr += (int)Humiditystat;
  ptr += "<span class=\"superscript\">%</span></div>\n";
  ptr += "</div>\n";

  ptr += "</div>\n";

  // set matrix intensity
  ptr += "<form action='/Brightness' method='GET'> Up: <input type='number' name='BrightnessUp' min='0' max='15' length='1' value=";
  ptr +=  String(BrightnessUp) + "> Lo: <input type='number' name='BrightnessLo' min='0' max='15' length='1' value=";
  ptr +=  String(BrightnessLo) + "><input type='submit' value='Set brightness'></form><br>\n";

  // set upper font
  ptr += "<form action='/Font' method='GET'> Upper font (1-3): <input type='number' name='FontUpNum' min='1' max='3' length='1' value=";
  ptr +=  String(FontUpNum) + "><input type='submit' value='Set font'></form>\n";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handleRoot() {
  //server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
  server.send(200, "text/html", SendHTML(dht.readTemperature(), dht.readHumidity()));
}

void handleBrightness() {

  //  if (server.args() > 0 ) {
  //    for ( uint8_t i = 0; i < server.args(); i++ ) {
  //      if (server.argName(i) == "BrightnessUp") {
  //        BrightnessUp = server.arg("BrightnessUp").toInt();
  //      }
  //      else if (server.argName(i) == "BrightnessLo") {
  //        BrightnessLo = server.arg("BrightnessLo").toInt();
  //      }
  //    }
  //  }

  BrightnessUp = server.arg("BrightnessUp").toInt();
  BrightnessLo = server.arg("BrightnessLo").toInt();
  WriteBrightness(); // to EEPROM
  P.setIntensity(ZONE_UPPER, BrightnessUp);
  P.setIntensity(ZONE_LOWER, BrightnessLo);

  PRINT("\nSet Brightness Up to: ", BrightnessUp);
  PRINT("\nSet Brightness Lo to: ", BrightnessLo);

  server.sendHeader("Location", "/");       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleFontNum() {

  FontUpNum = server.arg("FontUpNum").toInt();

  SetFontUpNum();

  WriteFontUpNum(); // to EEPROM

  PRINT("\nSet Upper font to: ", FontUpNum);

  server.sendHeader("Location", "/");       // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

//void handleLED() {                          // If a POST request is made to URI /LED
//  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
//  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
//  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
//}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not found");
}

void setup(void)
{
  Serial.begin(115200);
  Wire.begin();
  //pinMode(BUILTIN_LED, OUTPUT); //16, D0, LED_BUILTIN, BUILTIN_LED
  //pinMode(PIN_TONE, OUTPUT);

  //bytes 100, 101 - for upper & lower zones brightness
  //102 - FontUpNum
  //0 to 96 - for wifi ssid & pass (not implemented)
  EEPROM.begin(512); //Initialasing EEPROM

  //pinMode(DHT_PIN, INPUT);
  dht.begin();

  //set a time to start with.
  //day, weekday, month, century(1=1900, 0=2000), year(0-99)
  //RTC.setDate(12, 3, 8, 0, 20);
  //hr, min, sec
  //RTC.setTime(10, 58, 00);

  P.begin(NUM_ZONES);
  P.displaySuspend(false);
  P.setInvert(false);

  P.setZone(ZONE_UPPER, ZONE_SIZE, MAX_DEVICES - 1);
  P.setZone(ZONE_LOWER, 0, ZONE_SIZE - 1);

  //P.setIntensity(Brightness);
  ReadBrightness(); // from EEPROM
  P.setIntensity(ZONE_UPPER, BrightnessUp);
  P.setIntensity(ZONE_LOWER, BrightnessLo);

  //P.setFont(ZONE_UPPER, NumFontUpper);
  //P.setFont(ZONE_LOWER, NumFontLower);
  P.setCharSpacing(ZONE_UPPER, 1);
  P.setCharSpacing(ZONE_LOWER, 1);

  WiFi.begin(ssid, password);
  delay ( 500 );

  PRINT("\nConnecting to the WiFi Network named > ", ssid);

  P.setFont(ZONE_UPPER, NumFontUpper); //with abc
  P.setFont(ZONE_LOWER, NumFontUpper); //temporary

  P.displayZoneText(ZONE_LOWER, "WiFi...", PA_CENTER, SPEED_TIME_LOWER, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(ZONE_UPPER, "Wait", PA_CENTER, SPEED_TIME_UPPER, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayAnimate();

  WiFi.softAPdisconnect (true); //no Access point

  wifi_ok = true;
  uint32_t lastWifi = 0;
  while ( wifi_ok && WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    if ( (millis() - lastWifi) >= 10000 ) {
      wifi_ok = false;
    }
    PRINTS( "." );
  }

  ReadFontUpNum(); //from EEPROM
  SetFontUpNum();
  P.setFont(ZONE_LOWER, NumFontLower);
  P.displayZoneText(ZONE_LOWER, szMesg, PA_CENTER, SPEED_TIME_LOWER, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(ZONE_UPPER, szTime, PA_CENTER, SPEED_TIME_UPPER, 0, PA_PRINT, PA_NO_EFFECT);

  P.displayClear();
  PrintIP();

  timeClient.begin();
  timeClient.setTimeOffset(timeZone * 60 * 60);
  timeCheck();

  //  if (MDNS.begin("clock")) {              // Start the mDNS responder for clock.local
  //    PRINTS("\nmDNS responder started");
  //  } else {
  //    PRINTS("\nError setting up MDNS responder!");
  //  }
  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/Brightness", HTTP_GET, handleBrightness);
  server.on("/Font", HTTP_GET, handleFontNum);
  server.onNotFound(handleNotFound);
  server.begin();
  PRINTS("\nHTTP server started");

}

void loop(void)
{
  static uint32_t lastTime = 0; // millis() memory
  static uint32_t lastNTP = 0;
  static uint32_t lastDHT_T = 0;
  static uint32_t lastDHT_H = 0;
  static uint32_t lastDHT = 0;
  static bool flasher = true;  // seconds passing flasher

  P.displayAnimate();

  if (P.getZoneStatus(ZONE_UPPER))
  {
    P.setTextEffect(ZONE_UPPER, PA_PRINT, PA_NO_EFFECT);

    strcpy(szTime, szTimeNew);

    if ( m == 0 && s == 0 ) {
      P.setTextEffect(ZONE_UPPER, PA_RANDOM, PA_NO_EFFECT);
    }

    P.displayReset(ZONE_UPPER);
  }

  if (P.getZoneStatus(ZONE_LOWER))
  {
    P.setTextEffect(ZONE_LOWER, PA_PRINT, PA_NO_EFFECT);
    strcpy(szMesg, szMesgNew);
    P.displayReset(ZONE_LOWER);
  }

  // DHT data show
  if ( (millis() - lastDHT_T) >= 10000 ) {
    dht_H_flag = false;
    dht_T_flag = true; //show temperature
    lastDHT_T = millis();
  }
  if ( (millis() - lastDHT_H) >= 15000 ) {
    dht_T_flag = false;
    dht_H_flag = true; //show humidity
    lastDHT_T = millis();
    lastDHT_H = millis();
  }
  if ( (millis() - lastDHT) >= 18000 ) {
    // show week day
    dht_T_flag = false;
    dht_H_flag = false;
    lastDHT = millis();
    lastDHT_T = millis();
    lastDHT_H = millis();
  }

  //get+set date time from NTP
  if ( (millis() - lastNTP) > HALF_HRS ) {
    //if ( (millis() - lastNTP) > 30000 ) {
    lastNTP = millis();
    ntp_get = true;
    timeCheck();
  }

  //get date time from RTC
  if (millis() - lastTime >= 1000) {

    lastTime = millis();
    getDate(szMesgNew);
    getTime(szTimeNew, flasher);
    flasher = !flasher;

    //Set display brightness to (0-15)
    //    if ( h > 19 || h < 10 ) {
    //      BrightnessUp = 2;
    //      BrightnessLo = 2;
    //    }
    //    else {
    //      BrightnessUp = 4;
    //      BrightnessLo = 4;
    //    }

    //PRINT("\n WiFi status: ", WiFi.status());
    if (!wifi_ok && WiFi.status() == WL_CONNECTED)
    {
      wifi_ok = true;
      timeCheck();
      PrintIP();
    } else if (wifi_ok && WiFi.status() != WL_CONNECTED)
    {
      wifi_ok = false;
      PrintIP();
    }
  }

  server.handleClient();                    // Listen for HTTP requests from clients

} //END
