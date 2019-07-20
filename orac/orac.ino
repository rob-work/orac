// ORAC ring lights
// chase 16 LEDs round a loop in 1 second
// each cycle change red light set by turning on/off 12volts using TIP122s  
// each cycle fade the centre lights up and down

// set number of pins in array for chaser
int pinsCount = 16; 
                       
//setup these pins in an array for the sequence - 0 and 1 are reversed on the board, 3 is used for the fader
//this layout allows the efficient use of grouped pin connectors on a nano. 
int pins[] = {1,0,2,4,5,6,7,8,10,11,12,13,14,15,16,17};

//TIP1 and 2 switch TIP122 acting as a 12v relay   
int TIP1 = 18;
int TIP2 = 19;

//FADER pulses 2 LEDs
int FADER = 3;

//
int REED_PIN = 9; // Pin connected to reed switch
int brightness = 0;
int fadeamount = 1;
 
void setup() {  
  // counting the variable i from 0 to 15              
  for (int i=0; i<pinsCount; i=i+1){
    // initialising the pin at index i of the array of pins as OUTPUT      
    pinMode(pins[i], OUTPUT);             
  }
  pinMode(FADER, OUTPUT);
  pinMode(TIP1, OUTPUT); 
  pinMode(TIP2, OUTPUT);
  digitalWrite(TIP1, LOW);
  digitalWrite(TIP2, LOW);
  analogWrite(FADER, brightness);
  digitalWrite(TIP1, LOW);
  digitalWrite(TIP2, LOW);       
  pinMode(REED_PIN, INPUT_PULLUP);

}
 
void loop() {
  // Read the state of the switch, If the pin reads low, the switch is closed.
  int proximity = digitalRead(REED_PIN); 
  if (proximity == LOW) {
    for (int i=pinsCount-1; i>0; i=i-1){ 
      // switching the LED at index i on   
      digitalWrite(pins[i], HIGH);          
      //we use this time to fade up/down the pulsing LEDs
      for (int j=pinsCount-1; j>0; j=j-1){
        analogWrite(FADER, brightness);
        delay(4);
        brightness = brightness + fadeamount;
      }
      // reverse the direction of the fading at the ends of the fade:
      if (brightness <= 0 || brightness >= 255) {
        fadeamount = -fadeamount;
      } 
      // switching the LED at index i off
      digitalWrite(pins[i], LOW);           
    }  
    if(digitalRead(TIP1)==LOW) {
      //set 1 on, set 2 off
      digitalWrite(TIP1, HIGH);
      digitalWrite(TIP2, LOW);
    } else {
      //set 2 on set 1 off
      digitalWrite(TIP1, LOW);
      digitalWrite(TIP2, HIGH);
      }
  }
    //if out of loop turn off all lights as reed switch open
    digitalWrite(TIP1, LOW);
    digitalWrite(TIP2, LOW);
    analogWrite(FADER, 0);
}
