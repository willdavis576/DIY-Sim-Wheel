int outA = 9;
int outB = 10;

bool left;
bool right;
bool oldLeft;
bool oldRight;

int dir = 0; //true = clockwise, false = anti-clockwise

void setup() {
  // put your setup code here, to run once:
  pinMode(outA, INPUT_PULLUP);
  pinMode(outB, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  encoderRight();
}


void encoderRight() {
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

  if (dir != 2) { //output
    Serial.println(dir);
    dir = 2;
  }
}
