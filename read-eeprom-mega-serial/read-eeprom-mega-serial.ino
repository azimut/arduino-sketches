#define WE 20
#define OE 21

byte dataBits[] = {49,48,47,46,45,44,43,42}; // PORT L
byte addrBits[] = {22,23,24,25,26,27,28,29}; // PORT A

void setAddress(byte addr) {
  for (int i = 0; i < sizeof(addrBits); ++i) {
    digitalWrite(addrBits[i], addr & 0x01);
    addr = addr >> 1;
  }
}

byte readEEPROM(byte addr) {
  byte data = 0x00;
  setAddress(addr);
  digitalWrite(WE, HIGH);
  digitalWrite(OE, LOW);
  for (int i = sizeof(dataBits)-1; i >= 0; --i) {
    byte bit = digitalRead(dataBits[i]) ? 1 : 0;
    data = (data << 1) + bit;
  }
  digitalWrite(OE, HIGH);
  return data;
}

void printContents() {
  for (int base = 0; base <= 255; base += 16) {
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

  for (int i = 0; i < sizeof(dataBits); ++i) {
    pinMode(dataBits[i], INPUT);
  }
  for (int i = 0; i < sizeof(addrBits); ++i) {
    pinMode(addrBits[i], OUTPUT);
  }

  Serial.begin(57600);
  while (!Serial)
    ;
  Serial.println("reading...");
  delay(100);
  printContents();
  Serial.println("done!");
}

void loop() {}
