
#define BUTTON_PRESSED LOW
const int buttonPin = 2;     // the number of the pushbutton pin

const int greenPin =  32;
const int numberOLeds = 10;
int allPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, greenPin};


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

#define GAME_BUTTON_NOT_PRESSED 0
#define GAME_BUTTON_PRESSED 1
volatile byte state = GAME_BUTTON_NOT_PRESSED;

void setup() {
  // initialize the LED pin as an output:
//  pinMode(ledPin, OUTPUT);
  int i=0;
  for(i=0; i<numberOLeds; i++)
  {
    pinMode(allPins[i], OUTPUT);
  }
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); //enable interal pullup resister
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, CHANGE);

  // enable logging to serial
  Serial.begin(9600);
}

void loop() {
  

  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  while(buttonState != BUTTON_PRESSED)
  {
    buttonState = digitalRead(buttonPin);
  }
  digitalWrite(greenPin, HIGH);
  delay(500);
  digitalWrite(greenPin, LOW);
  buttonState = digitalRead(buttonPin);

  state = GAME_BUTTON_NOT_PRESSED;

  int increment = -1;
  int i=0;
  while(true)
  {
    digitalWrite(allPins[i], HIGH);
    delay(50);
    digitalWrite(allPins[i], LOW);

    if(state == GAME_BUTTON_PRESSED)
    {
      blinkPin(allPins[i],100,10);
      break;
    }
    
    if(i == (numberOLeds-1) || i == 0)
    {
      increment = increment * -1;
    }

    i = i + increment;
  }

  
}

void buttonPressed()
{
  state = GAME_BUTTON_PRESSED;
}

void blinkPin(int pin, int delayTime, int numberOfBlinks)
{
  int j = 0;
  for(j=0;j<numberOfBlinks;j++)
  {
    digitalWrite(pin, HIGH);
    delay(delayTime);
    digitalWrite(pin, LOW);
    delay(delayTime);
  }
}
