#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {7, 6, 5, 4};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char password[4];
int i = 0;
int counterror = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  char keyStroke = customKeypad.getKey();

  if (keyStroke == '*') {
    reset();
  } else if (keyStroke) {
    password[i++] = keyStroke;
    if (counterror < 3) {
    	Serial.println(keyStroke);
    }
  }

  if (i == 4) {
    delay(200);

    if (!(strncmp(password, "1234", 4))) {
      Serial.println("Bem vindo");
    } else {
      counterror++;
      if (counterror >= 1 && counterror <= 2) {
      	Serial.println("Errou");
        Serial.println(counterror);
      }
      if (counterror >= 3) {
        Serial.println("Voce errou 3 vezes a senha, o teclado esta travado");
      	char resetcommand = Serial.read();
        if (resetcommand == 'foobar') {
        	counterror = 0;
        }
      }
    }

    i = 0;
    delay(2000);
  }
}

void reset() {
  while (i != 0) {
    password[i--] = NULL;
  }

  Serial.println("Cleared...");
  delay(500);
}