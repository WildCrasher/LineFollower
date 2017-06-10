void initialize()
{
  pinMode(EN_11, OUTPUT);
  digitalWrite(EN_11,LOW);
  pinMode(EN_12, OUTPUT);
  digitalWrite(EN_12,LOW);
  pinMode(EN_21, OUTPUT);
  digitalWrite(EN_21,LOW);
  pinMode(EN_22, OUTPUT);
  digitalWrite(EN_22,LOW);
  pinMode(PWM1, OUTPUT);
  analogWrite(PWM1,0);
  pinMode(PWM2, OUTPUT);
  analogWrite(PWM2,0);
  pinMode(CZ_1, INPUT);
  pinMode(CZ_2, INPUT);
  pinMode(CZ_3, INPUT);
  pinMode(CZ_4, INPUT);
  pinMode(CZ_5, INPUT);
//  pinMode(LED,OUTPUT);
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(CS10) | _BV(WGM12);
}


