#include <Arduino.h>

#include "Wire.h"

#include "ssd1306.h"

#include "LSM303.h"

LSM303 cmps;

int i = 0;
unsigned long ts;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  cmps.init();
  cmps.enableDefault();

  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x32_i2c_init();

  ssd1306_clearScreen();

  Serial.println("started");

  cmps.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  cmps.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};

  ts = millis();
}


void loop()
{
  unsigned long now = millis();

  if (now - ts < 1000)
    return;

  ts += 1000;

  cmps.read();
  float heading = cmps.heading();

  Serial.println();
  Serial.print(i++);
  Serial.print("\t");
  Serial.print(heading);
  Serial.println();

  Serial.print("a:");
  Serial.print("\t");
  Serial.print(cmps.a.x);
  Serial.print("\t");
  Serial.print(cmps.a.y);
  Serial.print("\t");
  Serial.print(cmps.a.z);
  Serial.println();

  Serial.print("m:");
  Serial.print("\t");
  Serial.print(cmps.m.x);
  Serial.print("\t");
  Serial.print(cmps.m.y);
  Serial.print("\t");
  Serial.print(cmps.m.z);
  Serial.println();

  ssd1306_clearScreen();
  ssd1306_printFixed(0, 0, "Hello World", STYLE_NORMAL);
}

