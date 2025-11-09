#include <U8g2lib.h>
#include <WiFi.h>
#include "time.h"
#include "DHT.h"

// Externs from main sketch
extern U8G2_GP1294AI_256X48_F_4W_SW_SPI u8g2;
extern float cachedTemp, cachedHum, extTemp, extHum;

// Icons
extern const unsigned char image_wifi_connected_bits[];
extern const unsigned char image_wifi_disconnected_bits[];
extern const unsigned char image_humidity_bits[];
extern const unsigned char image_temperature_bits[];

// Helpers from main
const char* dow3(uint8_t wday);
void formatEnv(char* tempBuf, size_t tempLen, char* humBuf, size_t humLen, float t, float h);

// Helper for 12-hour format
uint8_t to12Hour(uint8_t hour24) {
  uint8_t h = hour24 % 12;
  return (h == 0) ? 12 : h;
}

// ------------------------ Drawing ------------------------
void drawUI(const struct tm& tmNow) {
  char timeHHMMSS[9];
  snprintf(timeHHMMSS, sizeof(timeHHMMSS), "%02d:%02d:%02d",
           to12Hour(tmNow.tm_hour),
           tmNow.tm_min, tmNow.tm_sec);

  const char* ampm = (tmNow.tm_hour < 12) ? "AM" : "PM";

  char dayOfMonth[3];
  snprintf(dayOfMonth, sizeof(dayOfMonth), "%02d", tmNow.tm_mday);

  char monthDay[10];
  snprintf(monthDay, sizeof(monthDay), "%02d %s", tmNow.tm_mon + 1, dow3(tmNow.tm_wday));

  const char* tzText = (tmNow.tm_isdst > 0) ? "BST" : "GMT";

  char tMain[8], hMain[8], tExt[8], hExt[8];
  formatEnv(tMain, sizeof(tMain), hMain, sizeof(hMain), cachedTemp, cachedHum);
  formatEnv(tExt,  sizeof(tExt),  hExt,  sizeof(hExt),  extTemp,   extHum);

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);

  // Panels
  u8g2.drawBox(187, 2, 45, 15);
  u8g2.drawBox(5, 28, 19, 18);
  u8g2.drawLine(5, 27, 5, 46);
  u8g2.drawFrame(187, 17, 45, 30);
  u8g2.drawBox(233, 28, 22, 17);
  u8g2.drawFrame(5, 27, 115, 20);

  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_timR24_tr);
  u8g2.drawStr(4, 25, timeHHMMSS);

  u8g2.setFont(u8g2_font_t0_15b_tr);
  u8g2.drawStr(7, 42, ampm);
  u8g2.setDrawColor(1);

  // Local env
  u8g2.setFont(u8g2_font_t0_14b_tr);
  u8g2.drawStr(35, 45, tMain);
  u8g2.drawXBM(25, 29, 9, 16, image_temperature_bits);
  u8g2.drawXBM(72, 29, 11, 16, image_humidity_bits);
  u8g2.drawStr(83, 45, hMain);

  // Wi-Fi
  if (WiFi.status() == WL_CONNECTED)
    u8g2.drawXBM(234, 3, 19, 16, image_wifi_connected_bits);
  else
    u8g2.drawXBM(234, 3, 19, 16, image_wifi_disconnected_bits);

  // Date
  u8g2.setFont(u8g2_font_profont29_tr);
  u8g2.drawStr(194, 42, dayOfMonth);

  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_t0_14b_tr);
  u8g2.drawStr(188, 14, monthDay);

  u8g2.setFont(u8g2_font_t0_12b_tr);
  u8g2.drawStr(235, 41, tzText);

  // External
  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_t0_14b_tr);
  u8g2.drawStr(142, 24, tExt);
  u8g2.drawXBM(128, 10, 9, 16, image_temperature_bits);
  u8g2.drawXBM(127, 29, 11, 16, image_humidity_bits);
  u8g2.drawStr(142, 43, hExt);

  u8g2.drawFrame(126, 8, 53, 39);
  u8g2.drawLine(126, 27, 178, 27);

  u8g2.drawBox(126, 2, 53, 6);
  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_4x6_tr);
  u8g2.drawStr(137, 8, "External");

  u8g2.sendBuffer();
}
