#include <stdint.h>
#include <math.h>

/**
 * The instance of this class can control single LED.
 * - on, off, toggle (any digital pin)
 * - brightness (only PWM pins; i.e. for Arduino Uno: 3, 5, 6, 9, 10, 11)
 */
class BasicLed {
public:
  BasicLed(uint8_t pin): pin_(pin) {
    pinMode(pin, OUTPUT); 
  }
  /* Light the LED up */
  void on(void) {
    digitalWrite(pin_, HIGH);
  }
  /* Turn the LED off */
  void off(void) {
    digitalWrite(pin_, LOW);
  }
  /* Toogle LED on/off */
  void toggle(void) {
    digitalWrite(pin_, !digitalRead(pin_));
  }
  /* Set LED brightness from range <0, 255> */
  void setBrightness(uint8_t value) {
    analogWrite(pin_, value);
  }
private:
  uint8_t pin_;
}; /* End of class BasicLed */

class LogarithmicFade {
public:
  LogarithmicFade(const BasicLed& led, uint16_t extra_delay_us = 3000) : 
    led_(led), extra_delay_us_(extra_delay_us) {}
  /* fade-in */
  void in(void) {
    for (int16_t i = 0; i < 255; (++i + step_increment)) {
      led_.setBrightness(i);
      sleep(i);
    }  
  }
  /* fade-out */
  void out(void) {
    for (int16_t i = 255; i >= 0; (--i - step_increment)) {
      led_.setBrightness(i);
      sleep(i);
    }
  }
  void setExtraDelay(uint16_t d) {
    extra_delay_us_ = d;
  }
  void setStepIncrement(uint16_t d) {
    step_increment = d;
  }
private:
  BasicLed led_;
  uint16_t step_increment = 0;
  uint16_t extra_delay_us_ = 0;
  
  void sleep(uint8_t i) {
    delayMicroseconds((uint16_t)(log(1. / (i + 1)) + 5.) * 1000);
    delayMicroseconds(extra_delay_us_);
  }
}; /* End of class LogarithmicFade */

class Blink {
public:
  Blink(const BasicLed& led, uint16_t extra_delay_us = 3000) : 
    led_(led), extra_delay_us_(extra_delay_us) {}

  void in(void) {
    for (int16_t i = 0; i < 255; (++i + step_increment)) {
      led_.setBrightness(i);
      sleep(i);
    }  
    for (int16_t i = 0; i < 255; (++i + step_increment)) {
      led_.setBrightness(i);
      sleep(i);
    }
  }
  void out(void) {
    led_.setBrightness(0);
  }
  void setExtraDelay(uint16_t d) {
    extra_delay_us_ = d;
  }
  void setStepIncrement(uint16_t d) {
    step_increment = d;
  }
private:
  BasicLed led_;
  uint16_t step_increment = 0;
  uint16_t extra_delay_us_ = 0;
  
  void sleep(uint8_t i) {
    delayMicroseconds((uint16_t)(log(1. / (i + 1)) + 5.) * 1000);
    delayMicroseconds(extra_delay_us_);
  }
}; /* End of class Blink */


// RGB LED Red 9, Green 10, Blue 11
BasicLed led(11);
LogarithmicFade fade(led);

BasicLed led2(10);
LogarithmicFade fade2(led2);

BasicLed led3(9);
LogarithmicFade fade3(led3);

// Pair of White LEDs
BasicLed led4(6);
//LogarithmicFade fade4(led4);
Blink fade4(led4);


void setup() {
  // do nothing
}

void loop() {
  fade.setExtraDelay(random(0,1000));
  fade2.setExtraDelay(random(0,2000));
  fade3.setExtraDelay(random(0,3000));

  fade4.setExtraDelay(random(0,5000));
  fade4.setStepIncrement(random(0,125));

  fade.in();
  fade2.in();
  fade3.in();

  fade4.in();

  fade.out();
  fade2.out();
  fade3.out();

  fade4.out();

}
