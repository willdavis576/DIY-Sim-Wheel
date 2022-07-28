int old;
int pind;
bool deb = false;
bool changeOverInc = false;
bool changeOverDec = false;
int debounce[] = {159, 189, 249, 243, 231, 207, 255};
int old2;
int pinc;
bool deb2 = false;
bool changeOverInc2 = false;
bool changeOverDec2 = false;
int debounce2[] = {39, 51, 57, 15, 63, 60, 30};

int upPin = 12;
int up;
int oldUp;

int crossPin = 11;
int cross;
int oldCross;


//encoders
int outA = 9;
int outB = 10;

bool left;
bool right;
bool oldLeft;
bool oldRight;

int dir = 0; //true = clockwise, false = anti-clockwise


//253, 251, 247, 239, 223, 191 -> clockwise
//159, 189, 249, 251,243, 231,207 -> bounce

void setup() {
  DDRD  &= B00000000; //0 - 7
  PORTD |= B11111111;

  DDRC  &= B00000000; //8 - 15
  PORTC |= B11111111;

  pinMode(upPin, INPUT_PULLUP);
  pinMode(crossPin, INPUT_PULLUP);

  pinMode(outA, INPUT_PULLUP);
  pinMode(outB, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  d();
  c();
  crossF();
  upF();
  encoderRight();
  Serial.println(PIND, BIN);
}

void encoderRight() { //thumb wheel encoder -> Brake Balance
  // clockwise = both, right, off, left, both, ..

  left = digitalRead(outA);
  right = digitalRead(outB);

  if (left == 1 && right == 1 && oldLeft == 1 && oldRight == 0) { //clockwise
    dir = 1;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 1 && right == 1 && oldRight == 1 && oldLeft == 0) { //anti-clockwise
    dir = 0;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 1 && right == 0 && oldLeft == 0 && oldRight == 0) { //clockwise
    dir = 1;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 1 && right == 0 && oldLeft == 1 && oldRight == 1) { //anti-clockwise
    dir = 0;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 0 && right == 1 && oldRight == 1 && oldLeft == 1) { //clockwise
    dir = 1;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 0 && right == 1 && oldRight == 0 && oldLeft == 0) { //anti-clockwise
    dir = 0;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 0 && right == 0 && oldRight == 1 && oldLeft == 0) { //clockwise
    dir = 1;
    oldLeft = left;
    oldRight = right;
  }

  if (left == 0 && right == 0 && oldLeft == 1 && oldRight == 0) { //anti-clockwise
    dir = 0;
    oldLeft = left;
    oldRight = right;
  }

  if (dir == 1) { //output
    Keyboard.set_modifier(MODIFIERKEY_SHIFT);
    Keyboard.set_key1(KEY_B);
    Keyboard.send_now();
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    dir = 2;
  }

  if (dir == 0) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL);
    Keyboard.set_key1(KEY_B);
    Keyboard.send_now();
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    dir = 2;
  }
}

void upF() {
  up = digitalRead(upPin);

  if (up != oldUp) {
    Keyboard.set_modifier(0);
    Keyboard.set_key1(KEY_INSERT);
    Keyboard.send_now();
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  oldUp = up;
}

void crossF() {
  cross = digitalRead(crossPin);

  if (cross != oldCross) {
    Keyboard.set_modifier(0);
    Keyboard.set_key1(KEY_ENTER);
    Keyboard.send_now();
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
  }
  oldCross = cross;
}

void c() {
  pinc = PINC;
  if (pinc == 62 && old2 == 31) {
    changeOverInc2 = true;
  }
  if (pinc == 31 && old2 == 62) {
    changeOverDec2 = true;
  }

  if (changeOverInc2 == true) {
    for (int i = 0; i < 7; i++) {
      if (pinc == debounce2[i]) {
        deb2 = true;
        //        break;
      }
    }
    if (deb2 == false) {
      Serial.print(PINC, BIN);
      Serial.print("\t");
      Serial.println(PINC);
      Keyboard.set_modifier(MODIFIERKEY_SHIFT);
      Keyboard.set_key1(KEY_A);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old2 = pinc;
    }
  }

  if (changeOverDec2 == true) {
    for (int i = 0; i < 7; i++) {
      if (pinc == debounce2[i]) {
        deb2 = true;
        //        break;
      }
    }
    if (deb2 == false) {
      Serial.print(PINC, BIN);
      Serial.print("\t");
      Serial.println(PINC);
      Keyboard.set_modifier(MODIFIERKEY_CTRL);
      Keyboard.set_key1(KEY_A);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old2 = pinc;
    }
  }

  if (pinc < old2 && changeOverInc2 == false) {
    for (int i = 0; i < 7; i++) {
      if (pinc == debounce2[i]) {
        deb2 = true;
        //        break;
      }
    }
    if (deb2 == false) {
      Serial.print(PINC, BIN);
      Serial.print("\t");
      Serial.println(PINC);
      Keyboard.set_modifier(MODIFIERKEY_SHIFT);
      Keyboard.set_key1(KEY_A);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old2 = pinc;
    }
  }


  if (pinc > old2 && changeOverDec2 == false) {
    for (int i = 0; i < 7; i++) {
      if (pinc == debounce2[i]) {
        deb2 = true;
        //        break;
      }
    }
    if (deb2 == false) {
      Serial.print(PINC, BIN);
      Serial.print("\t");
      Serial.println(PINC);
      Keyboard.set_modifier(MODIFIERKEY_CTRL);
      Keyboard.set_key1(KEY_A);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old2 = pinc;
    }
  }

  deb2 = false;
  changeOverInc2 = false;
  changeOverDec2 = false;
}

void d() {
  pind = PIND;

  if (pind == 253 && old == 191) {
    changeOverInc = true;
  }
  if (pind == 191 && old == 253) {
    changeOverDec = true;
  }

  if (changeOverInc == true) {
    for (int i = 0; i < 8; i++) {
      if (pind == debounce[i]) {
        deb = true;
        //        break;
      }
    }
    if (deb == false) {
      Keyboard.set_modifier(MODIFIERKEY_SHIFT);
      Keyboard.set_key1(KEY_T);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old = pind;
    }
  }

  if (changeOverDec == true) {
    for (int i = 0; i < 8; i++) {
      if (pind == debounce[i]) {
        deb = true;
        //        break;
      }
    }
    if (deb == false) {
      Keyboard.set_modifier(MODIFIERKEY_CTRL);
      Keyboard.set_key1(KEY_T);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old = pind;
    }
  }

  if (pind < old && changeOverInc == false) {
    for (int i = 0; i < 8; i++) {
      if (pind == debounce[i]) {
        deb = true;
        //        break;
      }
    }
    if (deb == false) {
      Keyboard.set_modifier(MODIFIERKEY_SHIFT);
      Keyboard.set_key1(KEY_T);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old = pind;
    }
  }


  if (pind > old && changeOverDec == false) {
    for (int i = 0; i < 8; i++) {
      if (pind == debounce[i]) {
        deb = true;
        //        break;
      }
    }
    if (deb == false) {
      Keyboard.set_modifier(MODIFIERKEY_CTRL);
      Keyboard.set_key1(KEY_T);
      Keyboard.send_now();
      Keyboard.set_modifier(0);
      Keyboard.set_key1(0);
      Keyboard.send_now();
      old = pind;
    }
  }

  deb = false;
  changeOverInc = false;
  changeOverDec = false;
}
