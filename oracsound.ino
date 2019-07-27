/*
    This example plays a random file (001 to 010) forever
    It uses the playFileAndWait() command so no extra code is needed, it will play another file as soon as the previous one finishes
    If it doesn't work, try reversing the RX/TX wires as that's probably going to be the most common mistake
    Also check that the player's BUSY line is connected to Arduino pin 3
    Finally check that the player has a speaker connected as well as ground and VCC
    file1 is start sound
    file2 is working sound
    file3 is stop sound
*/

#include "SoftwareSerial.h"
#include "MP3FLASH16P.h"
MP3FLASH16P myPlayer;
int REED_PIN = 9; // Pin connected to reed switch

void setup() {
    // Init the player with the busy pin connected to Arduino pin 3
    myPlayer.init(3);
}

void loop() {

  // Read the state of the switch,
  int proximity = digitalRead(REED_PIN); 
  
  if (proximity == HIGH) {
  
    // play start sound
    myPlayer.playFileAndWait(1, 30);

    // then play working sound
    myPlayer.playFile(2, 30);
    
    proximity = digitalRead(REED_PIN); 
    
    while (proximity ==HIGH) {
    //myPlayer.playFile(2, 30);
    //make short loop 1 sec
    myPlayer.playFileAndWait(2, 30); 
    proximity = digitalRead(REED_PIN);
    }
    myPlayer.playFileAndWait(3, 30);

  }
}
