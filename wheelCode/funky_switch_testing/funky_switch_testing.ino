int b1 = 8; //b1 push 
int b2 = 4; // UP
int b3 = 5; //b1 + b3 = RIGHT
int b4 = 6; //b1 + b4 = LEFT
int b5 = 7; //b1 + b5 = DOWN

int pinA = 3;
int pinB = 2;
volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte oldEncPos = 0;
volatile byte reading = 0;


int UP;
int RIGHT;
int LEFT;
int DOWN;
int IN;

int oldEncoderPos;




void setup() {
  // put your setup code here, to run once:
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b5, INPUT_PULLUP);
  pinMode (pinA, INPUT_PULLUP);
  pinMode (pinB, INPUT_PULLUP);

  attachInterrupt(0, PinA, RISING); // set an interrupt on PinA
  attachInterrupt(1, PinB, RISING); // set an interrupt on PinB,

  Serial.begin(115200);
}

void PinA(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void PinB(){
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void loop() {
    UP = digitalRead(b2);
    DOWN = digitalRead(b5);
    LEFT = digitalRead(b4);
    RIGHT = digitalRead(b3);
  
    if (UP == 1 && DOWN == 1 && LEFT == 1 && RIGHT == 1) {
      IN = digitalRead(b1);
    }

    if (encoderPos > oldEncoderPos) {
      UP = 1;
      DOWN = 0;
    }
    if (encoderPos < oldEncoderPos) {
      DOWN = 1;
      UP = 0;
    }

    oldEncoderPos = encoderPos;
    
  Serial.write(UP);
//  Serial.println("");
//  Serial.print(UP);
//  Serial.print("\t");
//  Serial.print(DOWN);
//  Serial.print("\t");
//  Serial.print(LEFT);
//  Serial.print("\t");
//  Serial.print(RIGHT);
//  Serial.print("\t");
//  Serial.print(IN);
//  Serial.print("\t");
//  Serial.print(encoderPos);

}
