int Fan = 8;

void setup()
{
    pinMode(Fan, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(Fan, HIGH);
    Serial.print(“Relay ch1 is HIGH”);
    delay(3000);
    
    digitalWrite(Fan, LOW);
    Serial.print(“Relay ch1 is LOW”);
    delay(3000);
}
