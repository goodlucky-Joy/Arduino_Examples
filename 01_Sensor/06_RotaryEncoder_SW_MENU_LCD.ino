#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#include <RotaryEncoder.h>
#include <Bounce2.h>

#define PIN_IN1 11 //Rotary Encoder DT Pin
#define PIN_IN2 12 //Rotary Encoder CLK Pin
#define Rotary_Encoder_SW 10   //Rotary Encoder SW Pin

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int mode = 0; // 0: init , 1: Monitoring , 2: Setting
int menu = 0;     // 0: Temperature , 1: Humidity , 2: light , 3: Soil Moisture
int currentMenu = 0;
int trig_signal = 30;

Bounce debouncer = Bounce();

void setup()
{
  lcd.begin(16,2);                                             
  lcd.backlight();
  lcd.init();                                  
  lcd.setCursor(0, 0);                            
  lcd.print("Hello, IASA");                      
  lcd.setCursor(0, 1);                            
  lcd.print("Welcome!"); 
  
  Serial.begin(115200);
  while (! Serial);
  Serial.println("SimpleRotator example");
  pinMode(Rotary_Encoder_SW, INPUT_PULLUP);
  debouncer.attach(Rotary_Encoder_SW);
  debouncer.interval(5);
}

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
      display_lcd(0,0, "Choose Mode");
      display_lcd(0,1, "                ");
    }  
    if(mode==0){  //초기화면
      if(currentMenu == 1){
        mode = 1;
        Serial.print("Monitoring Mode: ");
        Serial.println(mode);
        display_lcd(0,0, "Monitoring Mode");
      }
      if(currentMenu == 2){
        mode = 2;
        Serial.print("Setting Mode: ");
        Serial.println(mode);
        display_lcd(0,0, "Setting Mode");
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
  }//end of Push SW


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
      display_lcd(0,1, String(currentMenu));
    }
    if(mode==1){  //모니터링 모드
      currentMenu = (int)menu%5;
      Serial.print("Monitoring menu:");
      Serial.println(currentMenu);
      display_lcd(0,0, "Monitoring Mode");
      display_lcd(0,1, String(currentMenu));
    }
    if(mode==2){
      currentMenu = (int)menu%5;
      Serial.print("Setting menu:");
      Serial.println(currentMenu);
      
      display_lcd(0,0, "Setting Mode");
      display_lcd(0,1, String(currentMenu));
    }
  }//end of Rotation
}


void display_lcd(int c, int r, String str)
{
  lcd.setCursor(c, r);                            
  lcd.print("                ");
  lcd.setCursor(c, r);  
  lcd.print(str); 
}
