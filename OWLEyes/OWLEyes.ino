/*
 * Pretty OWL Smart Pet - Tests for OWL LED eyes
 * 
 * Arduino Lilypad Prototype Simple Circuit - 2x White LEDs, LDR Sensor, Button 
*/

int ledPin = 9;
int ledBrightness = 0;
int ledFadeAmount = 5;

int ldrPin = A2;
int ldrValue = 0;

int buttonPin = 5;
int buttonValue = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {

  /*
   * LDR Triggered
  ldrValue = analogRead(ldrPin);

  if ((ldrValue < 200))
  {
    digitalWrite(ledPin, HIGH); // turn on LEDs
    delay(1000);
  }
  digitalWrite(ledPin, LOW); // turn off LEDs
  delay(1000);
  */

  buttonValue = digitalRead(buttonPin);
  Serial.println(buttonValue);
  if (buttonValue == LOW) // button is on (HIGH) when unpressed
  {
    ledFadeInOut();
  }

  delay(500);
}

void ledBlink()
{

  digitalWrite(ledPin, HIGH); // turn on LEDs
  delay(50);
  digitalWrite(ledPin, LOW); // turn off LEDs
  delay(50);

}

// fade LEDs in/out using pulse width modulation (PWM) using ANALOGWRITE()
void ledFadeInOut()
{
  // set the brightness of pin 9:
  analogWrite(ledPin, ledBrightness);

  // change the brightness for next time through the loop:
  ledBrightness = ledBrightness + ledFadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (ledBrightness == 0 || ledBrightness == 255) {
    ledFadeAmount =- ledFadeAmount ;
  }

  delay(30);
}
