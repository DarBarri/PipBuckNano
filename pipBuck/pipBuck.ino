#include <OLED_I2C.h>
#include <SPI.h>
#include <Wire.h>

OLED  myOLED(SDA, SCL, 8);

static int Button1 = 7;
static int Button2 = 6;
static int SpeakerPin = 3;
static int ScreenLenght = 6;

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t logo[];
extern uint8_t science[];
extern uint8_t strenght[];

//pong
const unsigned long PADDLE_RATE = 33;
const unsigned long BALL_RATE = 16;
const uint16_t PADDLE_HEIGHT = 24;
uint16_t ball_x = 64, ball_y = 32;
uint16_t ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update;
unsigned long paddle_update;
const uint16_t CPU_X = 12;
uint16_t cpu_y = 16;
const uint16_t PLAYER_X = 115;
uint16_t player_y = 16;
long randGeigerTimeNumber;

void setup() {
  tone(SpeakerPin, 800);
  myOLED.begin();
  myOLED.setBrightness(10);
  myOLED.setFont(SmallFont);
  DrawCNDScreen();
  noTone(SpeakerPin);
  ball_update = millis();
  paddle_update = ball_update;
  randomSeed(analogRead(0));
  randGeigerTimeNumber = random(5, 40);
}
void DrawCNDScreen() {
  myOLED.setFont(SmallFont);
  myOLED.print(F("STATS lvl 30"), LEFT, 0);
  myOLED.print(F("HP 540/540"), LEFT, 8);
  myOLED.print(F("[CND]"), LEFT, 18);
  myOLED.print(F("RAD"), LEFT, 26);
  myOLED.print(F("EFF"), LEFT, 34);

  myOLED.drawBitmap(74, 11, logo, 52, 44);
  myOLED.print(F("(1)mem.sph.8"), LEFT, 44);
  //myOLED.print("", LEFT, 50);
  myOLED.setFont(TinyFont);
  myOLED.print(F("[stat]-SPECIAL-Skills-Perks-Gen"), LEFT, 56);
  LowerButtonGlow(0);
  myOLED.update();
}
void DrawRADScreen() {
  myOLED.setFont(SmallFont);
  myOLED.print(F("STATS lvl 30"), LEFT, 0);
  myOLED.print(F("HP 540/540"), LEFT, 8);
  myOLED.print(F("(6)RadX"), RIGHT, 18);
  myOLED.print(F("CND"), LEFT, 18);
  myOLED.print(F("(5)Rad-away"), RIGHT, 26);
  myOLED.print(F("[RAD]"), LEFT, 26);
  myOLED.print(F("EFF"), LEFT, 34);
  myOLED.print(F("rad_________|"), RIGHT, 40);
  myOLED.print(F("Res.80% "), LEFT, 45);
  myOLED.print(F("^320   "), RIGHT, 48);

  myOLED.setFont(TinyFont);
  myOLED.print(F("[stat]-SPECIAL-Skills-Perks-Gen"), LEFT, 56);
  LowerButtonGlow(0);
  myOLED.update();
}
void DrawEFFScreen() {
  myOLED.setFont(SmallFont);
  myOLED.print(F("STATS lvl 30"), LEFT, 0);
  myOLED.print(F("HP 540/540"), LEFT, 8);
  myOLED.print(F("CND"), LEFT, 18);
  myOLED.print(F("Taint:"), RIGHT, 10);
  myOLED.print(F("rad. heal."), RIGHT, 18);
  myOLED.print(F("limb regrow"), RIGHT, 26);
  myOLED.print(F("RAD"), LEFT, 26);
  myOLED.print(F("[EFF]"), LEFT, 34);

  myOLED.setFont(TinyFont);
  myOLED.print(F("[stat]-SPECIAL-Skills-Perks-Gen"), LEFT, 56);
  LowerButtonGlow(0);
  myOLED.update();
}
void DrawSPECIALScreen() {
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("lvl. 30", LEFT, 0);
  myOLED.print("HP 540/540", RIGHT, 0);

  myOLED.drawBitmap(37, 11, strenght, 52, 44);

  myOLED.print(F("Str. 4"), LEFT, 18);
  myOLED.print(F("Perc.7"), LEFT, 26);
  myOLED.print(F("End. 5"), LEFT, 34);
  myOLED.print(F("Char.4"), LEFT, 42);
  myOLED.print(F("Int. 8"), RIGHT, 18);
  myOLED.print(F("Agil.7"), RIGHT, 26);
  myOLED.print(F("Luck 5"), RIGHT, 34);

  myOLED.setFont(TinyFont);
  myOLED.print(F("stat-[SPECIAL]-Skills-Perks-Gen"), LEFT, 56);
  LowerButtonGlow(0);
  myOLED.update();
}
void DrawSkillsScreen() {
  myOLED.setFont(SmallFont);
  myOLED.print(F("STATS lvl 30"), LEFT, 0);
  myOLED.print(F("HP 540/540"), LEFT, 8);

  myOLED.print(F("Science  100"), LEFT, 18);
  myOLED.print(F("Lockpick 100"), LEFT, 26);
  myOLED.print(F("Firearms 100"), LEFT, 34);
  myOLED.print(F("Stealth  100"), LEFT, 42);

  myOLED.drawBitmap(74, 11, science, 52, 44);
  myOLED.setFont(TinyFont);
  myOLED.print(F("stat-SPECIAL-[Skills]-Perks-Gen"), LEFT, 56);
  LowerButtonGlow(0);
  myOLED.update();
}
void DrawPerksScreen() {
  myOLED.setFont(SmallFont);
  myOLED.print(F("STATS lvl 30"), LEFT, 0);
  myOLED.print(F("HP 540/540"), LEFT, 8);

  myOLED.print(F("Ch.La Filly|"), LEFT, 18);
  myOLED.print(F("Horse Sense|"), LEFT, 26);
  myOLED.print(F("Bookworm   |"), LEFT, 34);
  myOLED.print(F("Egghead    |"), LEFT, 42);

  myOLED.print(F("Organizer "), RIGHT, 18);
  myOLED.print(F("Light Trot"), RIGHT, 26);
  myOLED.print(F("Math Wrath"), RIGHT, 34);
  myOLED.print(F("St.   Shot"), RIGHT, 42);

  myOLED.setFont(TinyFont);
  myOLED.print(F("stat-SPECIAL-Skills-[Perks]-Gen"), LEFT, 56);
  LowerButtonGlow(0);
  myOLED.update();

}
bool restart = false;
void PongScreen() {
  bool update = false;
  unsigned long time = millis();
  static bool up_state = false;
  static bool down_state = false;
  up_state = IsButtonPressed(Button1);
  down_state = IsButtonPressed(Button2);

  if (time > ball_update) {
    uint8_t new_x = ball_x + ball_dir_x;
    uint8_t new_y = ball_y + ball_dir_y;

    // Check if we hit the vertical walls
    if (new_x == 0 || new_x == 127) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
      restart = true;
    }

    // Check if we hit the horizontal walls.
    if (new_y == 0 || new_y == 63) {
      ball_dir_y = -ball_dir_y;
      new_y += ball_dir_y + ball_dir_y;
    }

    // Check if we hit the CPU paddle
    if (new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    // Check if we hit the player paddle
    if (new_x == PLAYER_X
        && new_y >= player_y
        && new_y <= player_y + PADDLE_HEIGHT)
    {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    myOLED.clrPixel(ball_x, ball_y);
    myOLED.setPixel(new_x, new_y);
    ball_x = new_x;
    ball_y = new_y;

    ball_update += BALL_RATE;

    update = true;
  }

  if (time > paddle_update) {
    paddle_update += PADDLE_RATE;

    // CPU paddle
    myOLED.clrLine(CPU_X, cpu_y, CPU_X , cpu_y + PADDLE_HEIGHT);
    const uint16_t half_paddle = PADDLE_HEIGHT >> 1;
    if (cpu_y + half_paddle > ball_y) {
      cpu_y -= 1;
    }
    if (cpu_y + half_paddle < ball_y) {
      cpu_y += 1;
    }
    if (cpu_y < 1) cpu_y = 1;
    if (cpu_y + PADDLE_HEIGHT > 63) cpu_y = 63 - PADDLE_HEIGHT;
    myOLED.drawLine(CPU_X, cpu_y, CPU_X, cpu_y + PADDLE_HEIGHT);

    // Player paddle
    myOLED.clrLine(PLAYER_X, player_y, PLAYER_X, player_y + PADDLE_HEIGHT);
    if (up_state) {
      player_y -= 1;
    }
    if (down_state) {
      player_y += 1;
    }
    up_state = down_state = false;
    if (player_y < 1) player_y = 1;
    if (player_y + PADDLE_HEIGHT > 63) player_y = 63 - PADDLE_HEIGHT;
    myOLED.drawLine(PLAYER_X, player_y, PLAYER_X, player_y + PADDLE_HEIGHT);

    update = true;
  }

  if (update) {
    myOLED.update();
    update = false;
    if (restart) {
      restart = false;
      ball_x = 64;
      ball_y = 32;
      myOLED.clrScr();
      myOLED.setFont(SmallFont);
      myOLED.print(F("<-exit   "), CENTER, 26);
      myOLED.print(F("->restart"), CENTER, 34);
      myOLED.update();
      while (1) {
        up_state = IsButtonPressed(Button1);
        down_state = IsButtonPressed(Button2);
        if (up_state) {
          ChangeScreen();
          break;
        }
        if (down_state) {
          myOLED.clrScr();
          break;
        }
      }
    }
  }
}

static bool GeigerMode = true;
static bool DemoMODE = true;
static const long interval = 5000;
unsigned long previousMillis = 0;
unsigned long GeigerMillis = 0;
int screenID = 0;
bool DigitalDR = false;

//                                                           <-----------------------LOOP HERE
void loop() {
  unsigned long currentMillis = millis();
  if (GeigerMode) {
    if (currentMillis - GeigerMillis >= randGeigerTimeNumber * 1000) {
      GeigerMillis = currentMillis;
      tone(SpeakerPin, 50);
      noTone(SpeakerPin);
    }
  }
  if (DemoMODE) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      DigitalDR = true;
    }
  }
  if (screenID == 6)
    PongScreen();
  else if (IsButtonPressed(Button1))
    ChangeScreen();
}


void ChangeScreen() {
  myOLED.clrScr();
  screenID = (screenID > ScreenLenght ? 0 : screenID + 1);
  switch (screenID) {
    case 0:
      DrawCNDScreen();
      break;
    case 1:
      DrawRADScreen();
      break;
    case 2:
      DrawEFFScreen();
      break;
    case 3:
      DrawSPECIALScreen();
      break;
    case 4:
      DrawSkillsScreen();
      break;
    case 5:
      DrawPerksScreen();
      break;
    case 6:
      PongScreen();
      break;


    default:
      myOLED.clrScr();
      myOLED.setFont(SmallFont);
      myOLED.print(F("ERROR"), CENTER, 26);
      break;
  }
}

void drawCourt() {
  myOLED.drawRect(0, 0, 128, 64);
}

bool prevButtonState[] = {0, 0};

bool IsButtonPressed(int button) {
  bool IBP = false;
  bool DR = (digitalRead(button) == HIGH) || DigitalDR;
  if (DigitalDR)
    DigitalDR = false;
  int b = button - 6;

  if (DR && !prevButtonState[b]) {
    prevButtonState[b] = IBP = true;
  }
  else if (!DR) {
    prevButtonState[b] = IBP = false;
  }
  return IBP;
}

void LowerButtonGlow(int nmb) {
  analogWrite(A1, 0);
  analogWrite(A2, 0);
  analogWrite(A3, 0);
  switch (nmb) {
    case 0:
      analogWrite(A1, 128);
      break;
    case 1:
      analogWrite(A2, 128);
      break;
    case 2:
      analogWrite(A3, 128);
      break;
    default:
      break;
  }
}
