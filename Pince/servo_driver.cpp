#include "servo_driver.h"
#include "arduino.h"

void activate_stepper(int intervalle){
  // disable global interrupts vv
  cli();

  // clear both timer5 control registers
  TCCR5B = 0;
  TCCR5A = 0;

  // Initialize timer5 to zero
  TCNT5 = 0;

  // Set timer5 prescaler to 1024
  // Timer frequency = 15625 ticks/s
  TCCR5B |= (1 << WGM52) | (1 << CS50) | (1 << CS52);

  // Set interrupt "on compare" and specify compare value(one second)
  TIMSK5 |= (1 << OCIE5A);
  OCR5A = intervalle; //pour donner 125 Hz

  // enable global interrupts: ^^
  sei();

}
void deactivate_stepper(){
  // disable global interrupts vv
  cli();
  TIMSK5 &= (0 << OCIE5A);
  sei();

}

// interrupt Service Routine(pour comparaison sur timer 5)
ISR(TIMER5_COMPA_vect)   //avec timer Five
{
  sei();
  if(digitalRead(PIN_STEP)){
  digitalWrite(PIN_STEP, LOW);
  }
  else{
  digitalWrite(PIN_STEP, HIGH);
  }
}

void set_stepper_dir(STEPPER_DIR dir){
  digitalWrite(PIN_DIR, dir);
}
