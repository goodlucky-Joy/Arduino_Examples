int LED = 9;

void setup()
{
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop()
{, 
    digitalWrite(LED, HIGH);
    Serial.print(“Relay ch2 is HIGH”);
    delay(3000);
    
    digitalWrite(LED, LOW);
    Serial.print(“Relay ch2 is LOW”);
    delay(3000);
}
