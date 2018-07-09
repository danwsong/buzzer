const int OPEN = 0;
const int LOCKED = 1;

const int CLEAR = 2;
const int BUZZER = 0;

int buzzers[] = { 4, 11, 5, 10, 6, 9, 7, 8, 16, 15, 17, 3, 18, 12, 1, 13 };
int state;

int buzz[] = { 1, 1, 0, 1, 1 };

void setup() {
  pinMode(CLEAR, INPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(1, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(15, OUTPUT);

  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(15, HIGH);

  digitalWrite(BUZZER, LOW);

  state = OPEN;
}

unsigned long lastBuzz;
int buzzer;

void loop() {
  if (state == OPEN) {
    digitalWrite(BUZZER, LOW);
    for (int i = 0; i < sizeof(buzzers) / sizeof(int) / 2; i++) {
      int val = digitalRead(buzzers[2 * i]);
      if (val == HIGH) {
        digitalWrite(buzzers[2 * i + 1], LOW);
        state = LOCKED;
        buzzer = i;
        lastBuzz = millis();
        break;
      }
    }
  } else if (state == LOCKED) {
    if (millis() - lastBuzz < 750) {
      digitalWrite(BUZZER, buzz[(millis() - lastBuzz) / 150]);
    } else {
      digitalWrite(BUZZER, LOW);
    }
    int val = digitalRead(CLEAR);
    if (val == HIGH) {
      clear();
    }
  }
}

void clear() {
  state = OPEN;
  for (int i = 0; i < sizeof(buzzers) / sizeof(int) / 2; i++) {
    digitalWrite(buzzers[2 * i + 1], HIGH);
  }
}

