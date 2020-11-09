
int trigger_pin = 2;
int echo_pin = 3;
int buzzer_pin = 8; 
int duration;
float distanceCm; 
int PHYSICAL_DISTANCE = 250;
int LOOP_TIME = 500;

void setup ( ) {
        Serial.begin (9600); 
        pinMode (trigger_pin, OUTPUT); 
        pinMode (echo_pin, INPUT);
        pinMode (buzzer_pin, OUTPUT);
}

void loop ( ) {
    // reset the trigger pin
    digitalWrite (trigger_pin, LOW);
    delayMicroseconds (2);
    digitalWrite (trigger_pin, HIGH);
    delayMicroseconds (10);
    digitalWrite (trigger_pin, LOW);
    duration = pulseIn (echo_pin, HIGH);
    distanceCm = ((float)duration) * (float)0.0340 / 2;
    objectNear(distanceCm);
}

void distanceBeep(int distanceCm) {    
    // find percentage of distance
    double pt = ((float)distanceCm/(float)PHYSICAL_DISTANCE)*100;    
    Serial.print("percent ");
    Serial.println (pt);
    // dwell time
    int dwellTime = ((double)LOOP_TIME * (double)pt / (double)100);
    Serial.print("Dwell time ");
    Serial.print(dwellTime);
    tone(buzzer_pin, 350, 75);    
    delay (dwellTime);
    noTone(buzzer_pin);
}

void objectNear(int distanceCm){
  Serial.print("Distance ");
  Serial.println(distanceCm);
  if (distanceCm >= 0 && distanceCm <= PHYSICAL_DISTANCE) {
    distanceBeep(distanceCm);
    Serial.println (" Too Close! ");
   } else {
    Serial.println (" All Clear! ");          
    noTone(buzzer_pin);
    delay (LOOP_TIME);        
  } 
}
