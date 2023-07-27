#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>  // Not actually used but needed to compile
#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 11);
const char *msg;
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
#define TS_MINX 160
#define TS_MINY 911
#define TS_MAXX 894
#define TS_MAXY 158
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30
MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define BLACK 0x0000
int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GREY tft.color565(64, 64, 64);
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
#define LIME 0x07E0
#define MINPRESSURE 10
#define MAXPRESSURE 1000
TSPoint p;
bool buttonEnabled = true;
bool breakButtonEnabled = true;
char currentPage = '0';   // Indicates that we are at Home Screen
char selectedUnit = '0';  // Indicates the selected unit for the first example, cms or inches
void DrawButtonBack(int x_btn_back, int y_btn_back) {
  tft.fillRoundRect(x_btn_back, y_btn_back, 30, 30, 5, WHITE);
  tft.fillRoundRect(x_btn_back + 2, y_btn_back + 2, 26, 26, 5, YELLOW);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setCursor(x_btn_back + 7, y_btn_back + 7);
  tft.print("<");
}
void Home() {
  //Draw white frame
  tft.drawRect(0, 0, 319, 240, WHITE);

  //Print "Hello" Text
  tft.setCursor(80, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Welcome");

  tft.setCursor(145, 75);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("To");


  tft.setCursor(80, 120);
  tft.setTextColor(RED);
  tft.setTextSize(4);
  tft.print("CU Cafe");
  tft.fillRect(60, 180, 200, 40, RED);
  tft.drawRect(60, 180, 200, 40, WHITE);
  tft.setCursor(80, 188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Menu Card");
}
void Cat() {
  //Draw white frame
  tft.drawRect(0, 0, 319, 240, LIME);
  tft.fillRect(60, 40, 200, 40, VIOLET);
  tft.drawRect(60, 40, 200, 40, DARKBLUE);
  tft.setCursor(80, 48);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("STARTER");
  tft.drawRect(0, 0, 319, 240, LIME);
  tft.fillRect(60, 95, 200, 40, VIOLET);
  tft.drawRect(60, 95, 200, 40, DARKBLUE);
  tft.setCursor(80, 103);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("BANQUET");
  tft.drawRect(0, 0, 319, 240, LIME);
  tft.fillRect(60, 150, 200, 40, VIOLET);
  tft.drawRect(60, 150, 200, 40, DARKBLUE);
  tft.setCursor(80, 158);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("DESSERT");
  DrawButtonBack(24, 190);
  CatFun();
}

void Cancel() {
  // digitalWrite(13, HIGH);
  tft.fillScreen(BLACK);
  delay(50);
  tft.drawRect(0, 0, 319, 240, LIME);
  tft.fillRect(60, 40, 200, 40, VIOLET);
  tft.drawRect(60, 40, 200, 40, DARKBLUE);
  tft.setCursor(80, 48);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("STARTER");
  tft.drawRect(0, 0, 319, 240, LIME);
  tft.fillRect(60, 95, 200, 40, VIOLET);
  tft.drawRect(60, 95, 200, 40, DARKBLUE);
  tft.setCursor(80, 103);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("BANQUET");
  tft.drawRect(0, 0, 319, 240, LIME);
  tft.fillRect(60, 150, 200, 40, VIOLET);
  tft.drawRect(60, 150, 200, 40, DARKBLUE);
  tft.setCursor(80, 158);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("DESSERT");
  DrawButtonBack(24, 190);
  TSPoint p = ts.getPoint();
  // digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  Serial.print("X = ");
  p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
  p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
  Serial.print(p.x);
  Serial.print("\tY = ");
  Serial.print(p.y);
  Serial.print("\tPressure = ");
  Serial.println(p.z);  // used to check correct coordinates
  if (p.x > 50 && p.x < 95 && p.y > 45 && p.y < 190 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    delay(50);
    Starter();
    breakButtonEnabled = false;  //Disable button
    // delay(100);
    // sMenu();
  }
  if (p.x > 126 && p.x < 173 && p.y > 45 && p.y < 190 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    delay(50);
    Banquet();
    breakButtonEnabled = false;  //Disable button
    // delay(100);
    // sMenu();
  }
  if (p.x > 205 && p.x < 245 && p.y > 45 && p.y < 190 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    delay(50);
    Dessert();
    breakButtonEnabled = false;  //Disable button
    // delay(100);
    // sMenu();
  }
  // CatFun();
}

void Starter() {
  tft.drawRect(0, 0, 319, 240, WHITE);
  tft.fillScreen(VIOLET);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);  //Page border
  tft.drawCircle(302, 18, 14.5, BLACK);         // cancel button
  tft.fillCircle(302, 18, 14, YELLOW);
  tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);  //Dish1
  tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);  //Dish2
  tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);  //Dish3
  tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);
  tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
  tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);  //Call Waiter
  tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);  //Dish4
  tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);  //Dish5
  tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);  //Dish6
  tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
  tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);  //Bill
  tft.setCursor(60, 0);
  tft.setTextSize(3);
  tft.setTextColor(LIME);
  tft.print("   Menu");
  tft.setCursor(295, 5);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("x");
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setTextColor(BLACK);
  tft.setCursor(37, 47);
  tft.print(" Idli");
  tft.setCursor(37, 97);
  tft.print(" Nachos");
  tft.setCursor(37, 147);
  tft.print(" Fries");
  tft.setCursor(23, 197);
  tft.print(" Call Waiter");
  tft.setCursor(187, 47);
  tft.print(" Poha");
  tft.setCursor(187, 97);
  tft.print(" Momos");
  tft.setCursor(187, 147);
  tft.print(" Salad");
  tft.setCursor(227, 197);
  tft.print(" Bill");
  //  delay(500);
  while (true) {
    p = ts.getPoint();

    if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
      continue;
    }
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    Serial.print("\tPressure = ");
    Serial.println(p.z);  // used to check correct coordinates
    sMenu();
  }
}
void sMenu() {
  if (p.x > 2 && p.x < 33 && p.y > 213 && p.y <= 240 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
  }
  if (p.x > 60 && p.x < 103 && p.y > 15 && p.y <= 85 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish1");
    msg = "Idli Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
    tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);
    tft.setCursor(37, 47);
    // tft.println(" Idli");
    delay(70);
  }
  if (p.x > 130 && p.x < 172 && p.y > 15 && p.y < 90 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish2");
    msg = "Nachos Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 90, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
    tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);
    tft.setCursor(37, 97);
    // tft.println(" Nachos");
    delay(70);
  }
  if (p.x > 200 && p.x < 246 && p.y > 18 && p.y < 88 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish3");
    msg = "Fries Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 140, 100, 40, 8, WHITE);  //rgb led
    delay(70);
    tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //rgb led
    tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);  //rgb led
    tft.setCursor(37, 147);
    // tft.print(" Fries");
    delay(70);
  }
  if (p.x > 269 && p.x < 315 && p.y > 5 && p.y < 144 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Call Waiter");
    msg = "CallingWaiter";
    mySerial.println(msg);
    // transmit();
    // Serial.println(msg);
    tft.fillRoundRect(10, 190, 190, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
    tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);
    tft.setCursor(23, 197);
    // tft.print(" Call Waiter");
    delay(70);
  }
  if (p.x > 60 && p.x < 103 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish4");
    msg = "Poha Ordered";
    // Serial.println(msg);
    mySerial.println(msg);
    // transmit();
    tft.fillRoundRect(180, 40, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);
    tft.setCursor(187, 47);
    // tft.print(" Poha");
    delay(70);
  }
  if (p.x > 130 && p.x < 172 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish5");
    msg = "Momos Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(180, 90, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);
    tft.setCursor(187, 97);
    // tft.print(" Momos");
    delay(70);
  }
  if (p.x > 200 && p.x < 246 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish6");
    msg = "Salad Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(180, 140, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);
    tft.setCursor(187, 147);
    // tft.print(" Salad");
    delay(70);
  }
  if (p.x > 270 && p.x < 310 && p.y > 160 && p.y < 230 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Bill");
    msg = "Customer Bill";
    // transmit();
    Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(210, 190, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
    tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);
    tft.setCursor(227, 197);
    // tft.print(" Bill");
    delay(70);
  }
}
void Banquet() {
  tft.drawRect(0, 0, 319, 240, WHITE);
  tft.fillScreen(WHITE);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);  //Page border
  tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
  tft.drawCircle(302, 18, 14.5, BLACK);  // cancel button
  tft.fillCircle(302, 18, 14, YELLOW);
  tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);  //Dish1
  tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);  //Dish2
  tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);  //Dish3
  tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);
  tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
  tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);  //Call Waiter
  tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);  //Dish4
  tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);  //Dish5
  tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);  //Dish6
  tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
  tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);  //Bill
  tft.drawCircle(302, 18, 14.5, BLACK);            // cancel button
  tft.fillCircle(302, 18, 14, YELLOW);
  tft.setCursor(295, 5);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("x");
  tft.setCursor(60, 0);
  tft.setTextSize(3);
  tft.setTextColor(LIME);
  tft.print("   Menu");
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setTextColor(BLACK);
  tft.setCursor(37, 47);
  tft.print(" Roti");
  tft.setCursor(37, 97);
  tft.print(" Rice");
  tft.setCursor(37, 147);
  tft.print(" Curry");
  tft.setCursor(23, 197);
  tft.print(" Call Waiter");
  tft.setTextSize(2);
  tft.setCursor(187, 47);
  tft.print(" Paneer");
  tft.setCursor(187, 97);
  tft.print(" MixVeg");
  tft.setCursor(187, 147);
  tft.print(" Kofta");
  tft.setCursor(227, 197);
  tft.print(" Bill");
  //  delay(500);
  while (true) {
    p = ts.getPoint();

    if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
      continue;
    }
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
    bMenu();
  }
}
void bMenu() {
  if (p.x > 60 && p.x < 103 && p.y > 15 && p.y <= 85 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish1");
    msg = "Roti Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
    tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);
    tft.setCursor(37, 47);
    tft.println(" Roti");
    delay(70);
  }
  if (p.x > 130 && p.x < 172 && p.y > 15 && p.y < 90 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish2");
    msg = "Rice Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 90, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
    tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);
    tft.setCursor(37, 97);
    // tft.println(" Rice");
    delay(70);
  }
  if (p.x > 200 && p.x < 246 && p.y > 18 && p.y < 88 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish3");
    msg = "Curry Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 140, 100, 40, 8, WHITE);  //rgb led
    delay(70);
    tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //rgb led
    tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);  //rgb led
    tft.setCursor(37, 147);
    // tft.print(" Curry");
    delay(70);
  }
  if (p.x > 269 && p.x < 315 && p.y > 5 && p.y < 144 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Call Waiter");
    msg = "CallingWaiter";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(10, 190, 190, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
    tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);
    tft.setCursor(23, 197);
    // tft.print(" Call Waiter");
    delay(70);
  }
  if (p.x > 60 && p.x < 103 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish4");
    msg = "Paneer Ordered";
    // Serial.println(msg);
    mySerial.println(msg);
    // transmit();
    tft.fillRoundRect(180, 40, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);
    tft.setCursor(187, 47);
    // tft.print(" Paneer");
    delay(70);
  }
  if (p.x > 130 && p.x < 172 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish5");
    msg = "Mix Veg Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(180, 90, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);
    tft.setCursor(187, 97);
    // tft.print(" Mix Veg");
    delay(70);
  }
  if (p.x > 200 && p.x < 246 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish6");
    msg = "Kofta";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(180, 140, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);
    tft.setCursor(187, 147);
    // tft.print(" Kofta");
    delay(70);
  }
  if (p.x > 270 && p.x < 310 && p.y > 160 && p.y < 230 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Bill");
    msg = "Customer Bill";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(210, 190, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
    tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);
    tft.setCursor(227, 197);
    // tft.print(" Bill");
    delay(70);
  }
  if (p.x > 0 && p.x < 30 && p.y > 215 && p.y < 235 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // mySerial.println(msg);
    // msg = "Customer Bill";
    Cancel();
    // tft.fillScreen(BLACK);
    // Cat();
  }
  // Cancel();
}
void Dessert() {
  tft.drawRect(0, 0, 319, 240, WHITE);
  tft.fillScreen(WHITE);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);  //Page border
  tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);  //Dish1
  tft.drawCircle(302, 18, 14.5, BLACK);          // cancel button
  tft.fillCircle(302, 18, 14, YELLOW);
  tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);  //Dish2
  tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);  //Dish3
  tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);
  tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
  tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);  //Call Waiter
  tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);  //Dish4
  tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);  //Dish5
  tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
  tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);  //Dish6
  tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
  tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);  //Bill
  tft.drawCircle(302, 18, 14.5, BLACK);            // cancel button
  tft.fillCircle(302, 18, 14, YELLOW);
  tft.setCursor(295, 5);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print("x");
  tft.setCursor(60, 0);
  tft.setTextSize(3);
  tft.setTextColor(LIME);
  tft.print("   Menu");
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setTextColor(BLACK);
  tft.setCursor(37, 47);
  tft.print(" Donut");
  tft.setCursor(37, 97);
  tft.print(" Pastry");
  tft.setCursor(37, 147);
  tft.print(" Pie");
  tft.setCursor(23, 197);
  tft.print(" Call Waiter");
  tft.setCursor(187, 47);
  tft.print(" Rabdi");
  tft.setCursor(187, 97);
  tft.print(" Mousse");
  tft.setCursor(187, 147);
  tft.print(" Faluda");
  tft.setCursor(227, 197);
  tft.print(" Bill");
  //  delay(500);
  while (true) {
    p = ts.getPoint();
    if (p.z < MINPRESSURE || p.z > MAXPRESSURE) {
      continue;
    }
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
    dMenu();
  }
}
void dMenu() {
  if (p.x > 60 && p.x < 103 && p.y > 15 && p.y <= 85 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish1");
    msg = "Donut Ordered";
    // transmit();
    mySerial.println(msg);
    // Serial.println(msg);
    tft.fillRoundRect(30, 40, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(30, 40, 100, 40, 8, GOLD);
    tft.drawRoundRect(30, 40, 100, 40, 8, WHITE);
    tft.setCursor(37, 47);
    // tft.println(" Dish1");
    delay(70);
  }
  if (p.x > 130 && p.x < 172 && p.y > 15 && p.y < 90 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish2");
    msg = "Pastry Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 90, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(30, 90, 100, 40, 8, GOLD);
    tft.drawRoundRect(30, 90, 100, 40, 8, WHITE);
    tft.setCursor(37, 97);
    // tft.println(" Dish2");
    delay(70);
  }
  if (p.x > 200 && p.x < 246 && p.y > 18 && p.y < 88 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish3");
    msg = "Pie Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(30, 140, 100, 40, 8, WHITE);  //rgb led
    delay(70);
    tft.fillRoundRect(30, 140, 100, 40, 8, GOLD);   //rgb led
    tft.drawRoundRect(30, 140, 100, 40, 8, WHITE);  //rgb led
    tft.setCursor(37, 147);
    // tft.print(" Dish3");
    delay(70);
  }
  if (p.x > 269 && p.x < 315 && p.y > 5 && p.y < 144 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Call Waiter");
    msg = "CallingWaiter";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(10, 190, 190, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(10, 190, 190, 40, 8, CYAN);
    tft.drawRoundRect(10, 190, 190, 40, 8, WHITE);
    tft.setCursor(23, 197);
    // tft.print(" Call Waiter");
    delay(70);
  }
  if (p.x > 60 && p.x < 103 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish4");
    msg = "Rabdi Ordered";
    // Serial.println(msg);
    mySerial.println(msg);
    // transmit();
    tft.fillRoundRect(180, 40, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 40, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 40, 100, 40, 8, WHITE);
    tft.setCursor(187, 47);
    // tft.print(" Dish4");
    delay(70);
  }
  if (p.x > 130 && p.x < 172 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish5");
    msg = "Mousse Ordered";
    // transmit();
    mySerial.println(msg);
    // Serial.println(msg);
    tft.fillRoundRect(180, 90, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 90, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 90, 100, 40, 8, WHITE);
    tft.setCursor(187, 97);
    // tft.print(" Dish5");
    delay(70);
  }
  if (p.x > 200 && p.x < 246 && p.y > 137 && p.y < 210 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Dish6");
    msg = "Faluda Ordered";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(180, 140, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(180, 140, 100, 40, 8, GOLD);
    tft.drawRoundRect(180, 140, 100, 40, 8, WHITE);
    tft.setCursor(187, 147);
    // tft.print(" Dish6");
    delay(70);
  }
  if (p.x > 270 && p.x < 310 && p.y > 160 && p.y < 230 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // Serial.println("Bill");
    msg = "Customer Bill";
    // transmit();
    // Serial.println(msg);
    mySerial.println(msg);
    tft.fillRoundRect(210, 190, 100, 40, 8, WHITE);
    delay(70);
    tft.fillRoundRect(210, 190, 100, 40, 8, GREEN);
    tft.drawRoundRect(210, 190, 100, 40, 8, WHITE);
    tft.setCursor(227, 197);
    // tft.print(" Bill");
    delay(70);
  }
  if (p.x > 0 && p.x < 30 && p.y > 215 && p.y < 235 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    // mySerial.println(msg);
    // msg = "Customer Bill";
    Cancel();
    // tft.fillScreen(BLACK);
    // Cat();
  }
  // Cancel();
}
void CatFun() {
  // digitalWrite(13, HIGH);
  // if (Serial.available()) {
  //   mySerial.println(Serial.readString());  // send from bluetooth to serial
  if (p.x > 50 && p.x < 95 && p.y > 45 && p.y < 190 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    delay(50);
    Starter();
    breakButtonEnabled = false;  //Disable button
    // delay(100);
    // sMenu();
  }
  if (p.x > 126 && p.x < 173 && p.y > 45 && p.y < 190 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    delay(50);
    Banquet();
    breakButtonEnabled = false;  //Disable button
    // delay(100);
    // sMenu();
  }
  if (p.x > 205 && p.x < 245 && p.y > 45 && p.y < 190 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    delay(50);
    Dessert();
    breakButtonEnabled = false;  //Disable button
    // delay(100);
    // sMenu();
  }
  if (p.x > 257 && p.x < 300 && p.y > 15 && p.y < 40 && p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    tft.fillScreen(BLACK);
    Home();
  }
}
int oldcolor, currentcolor, currentpcolour;
void setup(void) {
  tft.reset();
  tft.begin(tft.readID());
  Serial.begin(9600);
  Serial.println();
  Serial.print("reading id...");
  delay(5000);
  Serial.println(tft.readID(), HEX);
  tft.fillScreen(BLACK);
  tft.setRotation(1);

  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setTextColor(tft.color565(255, 255, 0));
  tft.setCursor(30, 70);
  tft.print("  -->");
  tft.setCursor(10, 100);
  tft.print("  Food Menu");
  tft.setCursor(50, 140);
  tft.print("Loading...");
  delay(6000);
  // delay(5000);
  for (int i = 0; i < 250; i++) {
    tft.fillRect(BAR_MINY - 10, BLUEBAR_MINX, i, 10, RED);
    delay(0.000000000000000000000000000000000000000000000000001);
  }
  Serial.begin(9600);    //open the serial port
  mySerial.begin(9600);  // open the bluetooth serial port
  tft.fillScreen(BLACK);
  mySerial.println("Table 1 :");
  // Starter();
  Home();
  pinMode(13, OUTPUT);
}
void loop() {
  digitalWrite(13, HIGH);
  p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  // if (Serial.available()) {
  //   mySerial.println(Serial.readString());  // send from bluetooth to serial

  if (p.z > ts.pressureThreshhold) {
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    Serial.print("\tPressure = ");
    Serial.println(p.z);  // used to check correct coordinates
    if (p.x > 250 && p.x < 300 && p.y > 45 && p.y < 200 && buttonEnabled || currentPage == '0')
    // The user has pressed inside the red rectangle
    {
      buttonEnabled = false;  //Disable button

      //This is important, because the libraries are sharing pins
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);

      //Erase the screen
      tft.fillScreen(BLACK);
      Cat();
      delay(500);
    }
    delay(10);
  }
  // }
}