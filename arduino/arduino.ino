const byte ANODE_PINS[8] = {13, 12, 11, 10, 9, 8 , 7, 6};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

byte patterns[10][8][4] = {
{
  { 1, 1, 1, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 1, 1, 1 }
 },

 {
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 }
 },

 {
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 1, 1, 1, 1 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 1, 1, 1 }
 },

 {
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 1, 1, 1, 1 }
 },
 {
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 }
 },
 {
  { 1, 1, 1, 1 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 1, 1, 1, 1 }
 },
 {
  { 1, 1, 1, 0 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 1, 1, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 1, 1, 1 }
 },
 {
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 }
 },
 {
  { 1, 1, 1, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 1, 1, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 1, 1, 1 }
 },
 {
  { 1, 1, 1, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 0, 0, 1 },
  { 1, 1, 1, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 },
  { 0, 0, 0, 1 }
 }
  
};

byte negSign[8][4] = {
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 1, 1, 1, 1 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 },
  { 0, 0, 0, 0 }
}; 

void setup() {
  Serial.begin(115200);
  
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);

    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);    
  }
}

void allOff() {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);    
  }
}

void allOn() {
  for (byte i = 0; i < 8; i++) {
    digitalWrite(ANODE_PINS[i], LOW);
    digitalWrite(CATHODE_PINS[i], LOW);    
  }
}

void displayNumber(byte leftPattern[8][4], byte rightPattern[8][4]) {
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 8; j++) {
      if ((j < 4 && leftPattern[i][j] == 1) || (j > 3 && rightPattern[i][j-4] == 1)) {
        digitalWrite(CATHODE_PINS[j], LOW);
      }
      else {
        digitalWrite(CATHODE_PINS[j], HIGH);
      }
    }
    digitalWrite(ANODE_PINS[i], LOW);
    delay(1);
    digitalWrite(ANODE_PINS[i], HIGH);
  }
}

void loop() {
  while (!Serial.available());
  // allOff();
  int degrees = Serial.readString().toInt();

  // Ensure the degrees in farenheit is "in bounds"
  if (degrees > 99) {
    Serial.print("Temperature too high to display");
  } if (degrees < -9) {
    Serial.print("Temperature too low to display");
  }

  // Get the left and right digits - if the weather < 0, then the left digit will be a negative sign
  int rightDigit;
  int leftDigit;
  bool negative = false;
  if (degrees < 0) {
    rightDigit = degrees * (-1);
    negative = true;
  } else {
    rightDigit = degrees % 10;
    leftDigit = (degrees / 10) % 10;
  }

  // Display until the next input arrives
  while (!Serial.available()) {
    displayNumber(negative ? negSign :patterns[leftDigit] , patterns[rightDigit]);
  }

}
