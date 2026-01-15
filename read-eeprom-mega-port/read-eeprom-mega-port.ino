#define NBLOCKS 3
#define WE 4
#define OE 3

void setAddress(word addr) {
  DDRC = 0xff;
  DDRL = 0xff; // 1 = OUTPUT
  PORTC = (addr >> 0) & 0x00ff;
  PORTL = (addr >> 8) & 0x00ff;
}

byte readEEPROM(word addr) {
  byte data = 0x00;
  DDRA = 0x00;
  setAddress(addr);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, LOW);
  data = PINA;
  digitalWrite(OE, HIGH);
  return data;
}

void printContents() {
  for (int base = 0; base <= (NBLOCKS * 127)+1; base += 16) {
    byte data[16];
    for (int offset = 0; offset <= 15; offset += 1) {
      data[offset] = readEEPROM(base + offset);
    }
    char buf[80];
    sprintf(buf,
            "%03x:  %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x "
            "%02x %02x %02x %02x %02x",
            base, data[0], data[1], data[2], data[3], data[4], data[5], data[6],
            data[7], data[8], data[9], data[10], data[11], data[12], data[13],
            data[14], data[15]);
    Serial.println(buf);
  }
}

void setup() {
  digitalWrite(WE, HIGH);
  pinMode(WE, OUTPUT);
  digitalWrite(WE, HIGH);
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);

  DDRA = 0x00; // INPUT  DATA
  DDRC = 0xFF; // OUTPUT ADDR

  Serial.begin(57600);
  while (!Serial)
    ;
  Serial.println("port reading...");
  delay(100);
  printContents();
  Serial.println("done!");
}

void loop() {}
