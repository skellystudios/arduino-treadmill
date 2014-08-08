/*
  Button

 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int inputPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState = LOW;

int lightState = 0;
int i = 0;
int mutex = 0;

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastReadingTime = 0;  // the last time the output pin was toggled
long debounceDelay = 40;    // the debounce time; increase if the output flickers

long lastOutputTime = 0;
long outputDelay = 300;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(inputPin, INPUT);
  // initialize serial port
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(inputPin);


  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (((millis() - lastReadingTime) > debounceDelay)
      && (buttonState == LOW)
      && (mutex == 0)) {

    mutex = 1;
    i = i + 1;
    toggle_light();
    lastReadingTime = millis();


  }
  else {
    mutex = 0;
  }

  if ((millis() - lastOutputTime) > outputDelay) {
    Serial.print(i);
    i = 0;
    lastOutputTime = millis();
  }
}

void toggle_light() {
  if (lightState == 0) {
    digitalWrite(ledPin, HIGH);
    lightState = 1;
  } else {
    digitalWrite(ledPin, LOW);
    lightState = 0;
  }

}


