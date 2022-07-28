int cwS = A0;
int acwS = A1;

int cwRead;
int acwRead;

int cw = 3;
int acw = 5;

int cwPower;
int acwPower;

void setup() {
  pinMode(cwS, INPUT);
  pinMode(acwS, INPUT);

  pinMode(cw, OUTPUT);
  pinMode(acw, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  Serial.print(analogRead(cwS));
  Serial.print("\t");
  Serial.println(analogRead(acwS));
  cwRead = analogRead(cwS);
  acwRead = analogRead(acwS);

  cwPower = map(cwRead, 0, 1024, 0, 255);
  acwPower = map(acwRead, 0, 1024, 0, 255);

  //  Serial.print("cw ");
  //  Serial.print(cwRead);
  //  Serial.print("\t");
  //  Serial.print("cwPower ");
  //  Serial.print(cwPower);
  //  Serial.print("\t");
  //  Serial.print("acw ");
  //  Serial.print(acwRead);
  //  Serial.print("\t");
  //  Serial.print("acwPower ");
  //  Serial.println(acwPower);
  //  if (cwRead >= 155) {
  //    analogWrite(cw, cwPower);
  //  }
  //
  //  if (cwRead < 155) {
  //    analogWrite(cw, 0);
  //  }
  //
  //  if (acwRead >= 155) {
  //    analogWrite(acw, acwPower);
  //  }
  //
  //  if (acwRead < 155) {
  //    analogWrite(acw, 0);
  //  }

  analogWrite(cw, cwPower);
  analogWrite(acw, acwPower);
}
