/*
  Blink V2 eftir Matta 06/2012
 */
 
//number of leds
const int nLEDS = 8;

// array for the leds
int leds[nLEDS];

int ledsLen = sizeof(leds)/sizeof(leds[0]);

//random led
int randNum = 0;  

//select buttons (inputs, 5V)
int s0 = 0;
int s1 = 1;
int s2 = 2;
int s3 = 3;
int s4 = 4; //reset button

//0 - 4, 0 no button pressed etc
int buttonPressed = 0;

//constant for figuring low bound of HIGH via analogRead
int H = 880;

// the setup routine runs once when you press reset:
void setup() {                
  //initialize the array with the pin numbers 1,2 etc
  for (int i = 1; i <= ledsLen; i++) {
     leds[i-1] = i; 
  }
  // initialize the digital pins as an output.
  for (int i = 0; i < ledsLen; i++) {
     pinMode(leds[i], OUTPUT); 
  }
  
  //random seed, 2 unconnected pin
  randomSeed(analogRead(5)); 
}

//allar on, allar off
void regularBlink() {
  for (int i = 0; i < ledsLen; i++) {
    digitalWrite(leds[i], HIGH);    
  }    
  delay(250);
  for (int i = 0; i < ledsLen; i++) {
     digitalWrite(leds[i], LOW); 
  }
  delay(250);
}

//vixlblikk
//vixlar 1&3, 2&4 o.s.frv.
void alternatingBlink() 
{
  for (int i = 0; i < ledsLen; i++) {
     if ((i+1) % 2 != 0) digitalWrite(leds[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < ledsLen; i++) {
     if ((i+1) % 2 != 0) digitalWrite(leds[i], LOW);
  }
  for (int i = 0; i < ledsLen; i++) {
     if ((i+1) % 2 == 0) digitalWrite(leds[i], HIGH);
  }
  delay(250);
  for (int i = 0; i < ledsLen; i++) {
     if ((i+1) % 2 == 0) digitalWrite(leds[i], LOW);
  }
}

//led1 blinks, led2 blinks, etc
void rowBlink() 
{
  for (int i = 0; i < ledsLen; i++) {
     digitalWrite(leds[i], HIGH);
     delay(150);
     digitalWrite(leds[i], LOW);
  } 
}

//yeah
void randomBlink() 
{  
    if (randNum == 0) {
      randNum = random(leds[0],leds[ledsLen-1]+1);
    }
    else if (randNum == leds[0]) {
      if (1 < ledsLen) randNum = random(leds[1],leds[ledsLen-1]+1);
    }
    else if (randNum == leds[ledsLen-1]) {
      randNum = random(leds[0],leds[ledsLen-1]);
    }
    else {
      int rand3 = (int) random(leds[0],randNum);
      int rand4 = (int) random(randNum+1,leds[ledsLen-1]+1);
      int randTwo = (int) random(0,2);
      if (randTwo == 0) { 
        randNum = rand3; 
      }
      else if (randTwo == 1) { 
        randNum = rand4; 
      }
    }
    
    digitalWrite(randNum, HIGH);
    delay(100);
    digitalWrite(randNum, LOW);
    delay(100);
}

// the loop routine runs over and over again forever:
void loop() {
  
  s0 = analogRead(A0);
  s1 = analogRead(A1);
  s2 = analogRead(A2);
  s3 = analogRead(A3);
  s4 = analogRead(A4);
  
  if (s4 > H) {
    buttonPressed = 0; //reset
    for (int i = 0; i < ledsLen; i++) {
       digitalWrite(leds[0], LOW);   
    }
  }
  else if (s0 > H || buttonPressed == 1) {
    
      buttonPressed = 1;
      
      regularBlink();
  }
  else if (s1 > H || buttonPressed == 2) {
     buttonPressed = 2;
    
     alternatingBlink(); 
  }
  else if (s2 > H || buttonPressed == 3) {
     buttonPressed = 3;
    
     randomBlink(); 
  }
  else if (s3 > H || buttonPressed == 4) {
     buttonPressed = 4;
    
     rowBlink(); 
  }
  else if (s0 < H && s1 < H && s2 < H && s3 < H && s4 < H) { /* do nothing */ }
  else digitalWrite(leds[0], HIGH); // error
}

