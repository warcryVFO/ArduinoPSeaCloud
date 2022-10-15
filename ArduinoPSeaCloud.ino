// https://github.com/SukkoPera/PsxNewLib
#include <DigitalIO.h>
#include <PsxControllerBitBang.h>

// https://github.com/NicoHood/HID
#define HID_CUSTOM_LAYOUT
#define LAYOUT_JAPANESE
#include <HID-Project.h>

// PSコントローラー接続ピン
const byte PIN_PS2_ATT = 4;
const byte PIN_PS2_CMD = 3;
const byte PIN_PS2_DAT = 2;
const byte PIN_PS2_CLK = 5;

// PSXインスタンス
PsxControllerBitBang<PIN_PS2_ATT, PIN_PS2_CMD, PIN_PS2_DAT, PIN_PS2_CLK> psx;

// IIDX/DDR切り替えスイッチ接続ピン
const byte PIN_SW = 9;

// キーマッピング用変数
KeyboardKeycode mapSELECT;
KeyboardKeycode mapSTART;
KeyboardKeycode mapUP;
KeyboardKeycode mapRIGHT;
KeyboardKeycode mapDOWN;
KeyboardKeycode mapLEFT;
KeyboardKeycode mapL2;
KeyboardKeycode mapR2;
KeyboardKeycode mapL1;
KeyboardKeycode mapR1;
KeyboardKeycode mapTRIANGLE;
KeyboardKeycode mapCIRCLE;
KeyboardKeycode mapCROSS;
KeyboardKeycode mapSQUARE;

// 直前のボタンステータス保存用
int lastData = 0xffff;

void setup() {
  psx.begin();
  psx.read();
  unsigned int data = psx.getButtonWord();
  if (((data & PSB_PAD_RIGHT) != 0) && ((data & PSB_PAD_DOWN) != 0) && ((data & PSB_PAD_LEFT) != 0)) {
    // 方向キー左右下が押されている場合はpop'nモード
    mapSELECT = KEY_BACKSPACE;
    mapSTART = KEY_ENTER;
    mapUP = KEY_G;
    mapRIGHT = KEY_RESERVED;
    mapDOWN = KEY_RESERVED;
    mapLEFT = KEY_RESERVED;
    mapL2 = KEY_B;
    mapR2 = KEY_V;
    mapL1 = KEY_C;
    mapR1 = KEY_X;
    mapTRIANGLE = KEY_Z;
    mapCIRCLE = KEY_S;
    mapCROSS = KEY_D;
    mapSQUARE = KEY_F;
  } else {
    pinMode(PIN_SW, INPUT_PULLUP);
    if (digitalRead(PIN_SW)) {
      // 切り替えスイッチOFFの場合IIDXモード
      mapSELECT = KEY_BACKSPACE;
      mapSTART = KEY_ENTER;
      mapUP = KEY_LEFT_SHIFT;
      mapRIGHT = KEY_RESERVED;
      mapDOWN = KEY_LEFT_CTRL;
      mapLEFT = KEY_V;
      mapL2 = KEY_F;
      mapR2 = KEY_RESERVED;
      mapL1 = KEY_S;
      mapR1 = KEY_D;
      mapTRIANGLE = KEY_RESERVED;
      mapCIRCLE = KEY_C;
      mapCROSS = KEY_X;
      mapSQUARE = KEY_Z;
#if false
      // IIDX 2Pレイアウト
      mapSELECT = KEY_BACKSPACE;
      mapSTART = KEY_ENTER;
      mapUP = KEY_RIGHT_SHIFT;
      mapRIGHT = KEY_RESERVED;
      mapDOWN = KEY_RIGHT_CTRL;
      mapLEFT = KEY_COMMA;
      mapL2 = KEY_K;
      mapR2 = KEY_RESERVED;
      mapL1 = KEY_H;
      mapR1 = KEY_J;
      mapTRIANGLE = KEY_RESERVED;
      mapCIRCLE = KEY_M;
      mapCROSS = KEY_N;
      mapSQUARE = KEY_B;
#endif
    } else {
      // 切り替えスイッチOFFの場合DDRモード
      mapSELECT = KEY_BACKSPACE;
      mapSTART = KEY_ENTER;
      mapUP = KEY_UP;
      mapRIGHT = KEY_RIGHT;
      mapDOWN = KEY_DOWN;
      mapLEFT = KEY_LEFT;
      mapL2 = KEY_RESERVED;
      mapR2 = KEY_RESERVED;
      mapL1 = KEY_RESERVED;
      mapR1 = KEY_RESERVED;
      mapTRIANGLE = KEY_M;
      mapCIRCLE = KEY_COMMA;
      mapCROSS = KEY_N;
      mapSQUARE = KEY_B;
    }
  }

  NKROKeyboard.begin();
}

void loop() {
  psx.read();
  unsigned int data = psx.getButtonWord();

  if (lastData != data) {
    if (data & PSB_SELECT) {
      NKROKeyboard.add(mapSELECT);
    } else {
      NKROKeyboard.remove(mapSELECT);
    }
    if (data & PSB_START) {
      NKROKeyboard.add(mapSTART);
    } else {
      NKROKeyboard.remove(mapSTART);
    }
    if (data & PSB_PAD_UP) {
      NKROKeyboard.add(mapUP);
    } else {
      NKROKeyboard.remove(mapUP);
    }
    if (mapRIGHT != KEY_RESERVED) {
      if (data & PSB_PAD_RIGHT) {
        NKROKeyboard.add(mapRIGHT);
      } else {
        NKROKeyboard.remove(mapRIGHT);
      }
    }
    if (mapDOWN != KEY_RESERVED) {
      if (data & PSB_PAD_DOWN) {
        NKROKeyboard.add(mapDOWN);
      } else {
        NKROKeyboard.remove(mapDOWN);
      }
    }
    if (mapLEFT != KEY_RESERVED) {
      if (data & PSB_PAD_LEFT) {
        NKROKeyboard.add(mapLEFT);
      } else {
        NKROKeyboard.remove(mapLEFT);
      }
    }
    if (mapL2 != KEY_RESERVED) {
      if (data & PSB_L2) {
        NKROKeyboard.add(mapL2);
      } else {
        NKROKeyboard.remove(mapL2);
      }
    }
    if (mapR2 != KEY_RESERVED) {
      if (data & PSB_R2) {
        NKROKeyboard.add(mapR2);
      } else {
        NKROKeyboard.remove(mapR2);
      }
    }
    if (mapL1 != KEY_RESERVED) {
      if (data & PSB_L1) {
        NKROKeyboard.add(mapL1);
      } else {
        NKROKeyboard.remove(mapL1);
      }
    }
    if (mapR1 != KEY_RESERVED) {
      if (data & PSB_R1) {
        NKROKeyboard.add(mapR1);
      } else {
        NKROKeyboard.remove(mapR1);
      }
    }
    if (data & PSB_TRIANGLE) {
      NKROKeyboard.add(mapTRIANGLE);
    } else {
      NKROKeyboard.remove(mapTRIANGLE);
    }
    if (data & PSB_CIRCLE) {
      NKROKeyboard.add(mapCIRCLE);
    } else {
      NKROKeyboard.remove(mapCIRCLE);
    }
    if (data & PSB_CROSS) {
      NKROKeyboard.add(mapCROSS);
    } else {
      NKROKeyboard.remove(mapCROSS);
    }
    if (data & PSB_SQUARE) {
      NKROKeyboard.add(mapSQUARE);
    } else {
      NKROKeyboard.remove(mapSQUARE);
    }

    // キー押下状態の更新
    NKROKeyboard.send();

    // 直前のボタンステータス更新
    lastData = data;
  }

  delay(1);
}