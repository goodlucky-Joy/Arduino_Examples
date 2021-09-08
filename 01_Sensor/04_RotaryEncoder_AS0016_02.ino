int aPin = 5;       //DT Pin
int bPin = 6;      //CLK Pin
int buttonPin = 7;  //SW Pin

int temp;
int temprotation = 100;
int rotation;

void setup() {
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  int change = getEncoderTurn();
  if(change!=temp){
    rotation = rotation+change;
    if(rotation != temprotation){
      Serial.println(rotation);
    }
    temprotation = rotation;
  }
  temp = change;
  delay(1);
}

int getEncoderTurn(){
  //return -1, 0, or +1
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;

  int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  if(newA != oldA || newB != oldB){
    if(oldA == LOW && newA == HIGH){
      if(newB==LOW){
        result--;
      }else{
        result++;
      }
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}
