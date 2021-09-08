#include <RotaryEncoder.h>
#include <Bounce2.h>

#define PIN_IN1 11 //Rotary Encoder DT Pin
#define PIN_IN2 12 //Rotary Encoder CLK Pin
#define Rotary_Encoder_SW 10   //Rotary Encoder SW Pin

#define ROTARYMAX 10
#define ROTARYMIN 0
#define ROTARYSTEPS 1

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int mode = 0; // 0: init , 1: Monitoring , 2: Setting
int menu = 0;     // 0: Temperature , 1: Humidity , 2: light , 3: Soil Moisture
int currentMenu = 0;
int trig_signal = 30;

Bounce debouncer = Bounce();

void setup()
{
  Serial.begin(115200);
  while (! Serial);
  Serial.println("SimplePollRotator example for the RotaryEncoder.");
  pinMode(Rotary_Encoder_SW, INPUT_PULLUP);
  debouncer.attach(Rotary_Encoder_SW);
  debouncer.interval(5);
}

// Read the current position of the encoder and print out when changed.
void loop()
{
  enterMenu();
}

void enterMenu()
{
  static int pos = 0;
  encoder.tick();

  //스위치를 눌렀을 경우
  debouncer.update(); 
  if(debouncer.fell()){
    encoder.setPosition(0);
    Serial.print("Push!");
    //Serial.print(" pos:");
    //Serial.print(pos);  
    menu = 1;
    //Serial.print(" mode:");
    //Serial.println(mode);
    if(currentMenu == 0){ //초기화면으로 돌아가기
      mode = 0;
    }  
    if(mode==0){  //초기화면
      if(currentMenu == 1){
        Serial.print("Monitoring Mode: ");
        mode = 1;
        Serial.println(mode);
      }
      if(currentMenu == 2){
        Serial.print("Setting Mode: ");
        mode = 2;
        Serial.println(mode);
      }
    }
    if(mode==1){   //모니터링모드
      Serial.print("Monitoring Mode: ");
      Serial.print(mode);
    }
    if(mode==2){   //셋팅모드
      Serial.print("Setting Mode: ");
      Serial.println(mode);
    }
  }

  //스위치를 돌렸을 경우
  int newPos = encoder.getPosition();  
  if (pos != newPos) {
    //Serial.print("Trun!");
    //Serial.print("pos:");
    //Serial.print(newPos);
    pos = newPos;
    
    if((int)encoder.getDirection()==1)
      menu = menu + 1;
    else
      menu = menu - 1;
    
    if(mode==0){  //초기화면
      currentMenu = (int)menu%3;
      Serial.print("Choose Mode: ");
      Serial.println(currentMenu);
    }
    if(mode==1){  //모니터링 모드
      currentMenu = (int)menu%5;
      Serial.print("Monitoring menu:");
      Serial.println(currentMenu);
    }
    if(mode==2){
      currentMenu = (int)menu%5;
      Serial.print("Setting menu:");
      Serial.println(currentMenu);
    }
  }
}
