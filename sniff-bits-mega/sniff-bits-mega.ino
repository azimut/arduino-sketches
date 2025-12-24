#define SYNC 21

// L - 8 data bits
// A - 8 addr lower bits
// C - 3 addr higher bits

byte sniffData() {
  DDRL = 0x00;
  byte data = 0x00;
  data = PINL;
  return data;
}
word sniffAddress() {
  DDRA = 0x00;
  DDRC = 0x00;
  word result = 0x0000;
  result = PINC & 0x0007;
  result = result << 8;
  result = result | PINA;
  return result;
}

void onClock() {
  word addr = sniffAddress();
  byte data = sniffData();
  char out[20];
  sprintf(out, "%04x %02x", addr, data);
  Serial.println(out);
}

void setup() {
  Serial.begin(57600);
  while (!Serial)
    ;

  DDRA = 0x00;
  DDRC = 0x00;
  DDRL = 0x00;

  attachInterrupt(digitalPinToInterrupt(SYNC),onClock,FALLING);
}

void loop() {}
