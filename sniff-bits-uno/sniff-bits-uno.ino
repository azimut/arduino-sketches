// B | D8-13 | 6 data lower  bits
// C | A0,A1 | 2 data higher bits (on lower)
// C | A2-A5 | 4 addr lower  bits
// D | D4-D7 | 4 addr higher bits (on higher)

#define SYNC 2

byte sniffAddress() {
  byte result = 0x00;
  result = PIND & 0xF0;
  result = result | ((PINC & 0x3C) >> 2);
  return result;
}

byte sniffData() {
  byte result = 0x00;
  result = PINC & 0x03;
  result = result << 6;
  result = result | (PINB & 0x3F);
  return result;
}

void onClock() {
  byte addr = sniffAddress();
  byte data = sniffData();
  char out[20];
  sprintf(out, "%02x: %02x", addr, data);
  Serial.println(out);
}

void setup() {
  Serial.begin(57600);
  while (!Serial);
  DDRB = DDRC = 0x00;
  DDRD = DDRD & 0x0B;
  attachInterrupt(digitalPinToInterrupt(SYNC),onClock,FALLING);
}

void loop() {}
