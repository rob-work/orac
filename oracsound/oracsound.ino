const int REED_PIN = 2; // Pin connected to reed switch
const int startPin = 4;
const int workingPin = 5;
const int stopPin = 6;
const int led = 17;
int proximity = 1;
unsigned long timeRunning;
unsigned long timeNow;
  
void setup() {
  pinMode(startPin, OUTPUT);
  pinMode(workingPin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(REED_PIN, INPUT);

  //set pins to off
  digitalWrite(startPin, HIGH);
  digitalWrite(workingPin, HIGH);
  digitalWrite(stopPin, HIGH);
  digitalWrite(led, LOW);
 
}

void loop() {

  // Read the state of the switch,
  proximity = digitalRead(REED_PIN); 

  if (proximity == LOW) {  
      digitalWrite(startPin, LOW);

      delay(200);
      digitalWrite(startPin, HIGH);
      delay(1000);
      
      digitalWrite(workingPin, LOW);
      delay(220);
      digitalWrite(workingPin, HIGH);
      delay(1000);


      //set time
      timeRunning = millis();
      while (proximity == LOW) {
        proximity = digitalRead(REED_PIN);
        digitalWrite(led, HIGH);
        timeNow = millis();
        //the working sound lasts about 30 secs, this replays it when it fades out
        if(timeNow >= (timeRunning + 30000)) {
              digitalWrite(workingPin, LOW);
              delay(220);
              digitalWrite(workingPin, HIGH);
              timeRunning = millis();
              
        }

      }   
          digitalWrite(led, LOW);
          digitalWrite(stopPin, LOW);
          delay(220);
          digitalWrite(stopPin, HIGH);
          delay(1000);
          exit;

  } else {
    delay(100);
  }

}
