#include <DigitalIO.h>
#include <PsxControllerBitBang.h>

#define SERIAL_MONITOR

const byte PIN_SW = 9;

const byte PIN_PS2_ATT = 4;
const byte PIN_PS2_CMD = 3;
const byte PIN_PS2_DAT = 2;
const byte PIN_PS2_CLK = 5;

PsxControllerBitBang<PIN_PS2_ATT, PIN_PS2_CMD, PIN_PS2_DAT, PIN_PS2_CLK> psx;

void setup() {
  pinMode(PIN_SW, INPUT_PULLUP);

#ifdef SERIAL_MONITOR
  Serial.begin(115200);
#endif
}

void loop() {
  int sw = digitalRead(PIN_SW);
  psx.begin();
  psx.read();

  unsigned int data = psx.getButtonWord();
#ifdef SERIAL_MONITOR
  Serial.print(sw);
  Serial.println(data);
#endif

  delay(100);
}