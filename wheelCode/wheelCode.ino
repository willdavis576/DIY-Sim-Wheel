const int leftBottomRed = 21;
const int leftBlue = 19;
const int leftTopBlack = 18;
const int rightBottomRed = 34;
const int psButton = 35;
const int rightBlue = 32;
const int rightTopRed = 33;
const int rightTopWhite = 25;
const int rightTopBlack = 26;
const int leftTopRed = 27;
const int leftTopWhite = 14;

int lbr = 0;
int lb = 0;
int ltb = 0;
int rbr = 0;
int psb = 0;
int rb = 0;
int rtr = 0;
int rtw = 0;
int rtb = 0;
int ltr = 0;
int ltw = 0;
void setup() {
  Serial.begin(115200);
  pinMode(leftBottomRed, INPUT);
  pinMode(leftBlue, INPUT);
  pinMode(leftTopBlack, INPUT);
  pinMode(rightBottomRed, INPUT);
pinMode(psButton, INPUT);
pinMode(rightBlue, INPUT);
pinMode(rightTopRed, INPUT);
pinMode(rightTopWhite, INPUT);
pinMode(rightTopBlack, INPUT);
pinMode(leftTopRed, INPUT);
pinMode(leftTopWhite, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
lbr = digitalRead(leftBottomRed);
lb = digitalRead(leftBlue);
ltb = digitalRead(leftTopBlack);
rbr = digitalRead(rightBottomRed);
psb = digitalRead(psButton);
rb = digitalRead(rightBlue);
rtr = digitalRead(rightTopRed);
rtw = digitalRead(rightTopWhite);
rtb = digitalRead(rightTopBlack);
ltr = digitalRead(leftTopRed);
ltw = digitalRead(leftTopWhite);

if (lbr == 1) {
  Serial.println("lbr");
}

if (lb == 1) {
  Serial.println("lb");
}

if (ltb == 1) {
  Serial.println("ltb");
}

if (rbr == 1) {
  Serial.println("rbr");
}

if (psb == 1) {
  Serial.println("psb");
}

if (rb == 1) {
  Serial.println("rb");
}

if (rtr == 1) {
  Serial.println("rtr");
}

if (rtw == 1) {
  Serial.println("rtw");
}

if (rtb == 1) {
  Serial.println("rtb");
}

if (ltr == 1) {
  Serial.println("ltr");
}

if (ltw == 1) {
  Serial.println("ltw");
}
}
