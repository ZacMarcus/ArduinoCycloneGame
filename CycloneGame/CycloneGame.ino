
#define BUTTON_PRESSED LOW
const int buttonPin = 2;     // the number of the pushbutton pin

const int greenPin =  31;
const int numberOLeds = 10;
int allPins[] = {22, 23, 24, 25, 26, 27, 28, 29, 30, greenPin};
int rgbPins[] = {10, 11, 12};

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

#define GAME_BUTTON_NOT_PRESSED 0
#define GAME_BUTTON_PRESSED 1
volatile byte state = GAME_BUTTON_NOT_PRESSED;

void setup() {
  // initialize the LED pin as an output:
  int i=0;
  for(i=0; i<numberOLeds; i++)
  {
    pinMode(allPins[i], OUTPUT);
  }
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); //enable interal pullup resister
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, CHANGE);

  //set difficulty led
  pinMode(rgbPins[0], OUTPUT);
  pinMode(rgbPins[1], OUTPUT);
  pinMode(rgbPins[2], OUTPUT);

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

  Serial.println("start");

  const int numberOfRounds = 5;
  int delay = 0;
  int i=0;
  for(i=0; i<numberOfRounds;)
  {
    switch(i)
    {
      case 0:
        RGB_color(0, 255, 0);
        delay = 120;
        break;
      case 1:
        RGB_color(255, 64, 0);
        delay = 100;
        break;
      case 2:
        RGB_color(255, 32, 0);
        delay = 80;
        break;
      case 3:
        RGB_color(255, 16, 0);
        delay = 60;
        break;
      case 4:
        RGB_color(255, 0, 0);
        delay = 40;
        break;
      
    }
    
    bool success = playRound(delay);
    if(success)
    {
      //Serial.println("success");
      i = i + 1;
    }
    else
    {
      //Serial.println("failed");
      i = 0;
    }
    
  }
  

  
}

bool playRound(int timeDelay)
{
  state = GAME_BUTTON_NOT_PRESSED;
  int increment = -1;
  int i=0;
  while(true)
  {
    int currentLed = allPins[i];
    digitalWrite(currentLed, HIGH);
    delay(timeDelay);
    digitalWrite(currentLed, LOW);

    if(state == GAME_BUTTON_PRESSED)
    {
      blinkPin(currentLed,100,10);

      if(currentLed == greenPin)
      {
        return true;
      }
      else
      {
        return false;
      }
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

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(rgbPins[0], red_light_value);
  analogWrite(rgbPins[1], green_light_value);
  analogWrite(rgbPins[2], blue_light_value);
}
