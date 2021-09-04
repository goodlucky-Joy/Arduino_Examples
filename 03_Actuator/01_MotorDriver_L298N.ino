int A1 = 12;
int A2 = 10;

void setup()
{
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  delay(2000);

  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  delay(2000);
}
