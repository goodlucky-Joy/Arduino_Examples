#include <RotaryEncoder.h>
#include <Bounce2.h>

#define PIN_IN1 11 //Rotary Encoder DT Pin
#define PIN_IN2 12 //Rotary Encoder CLK Pin
#define Rotary_Encoder_SW 10   //Rotary Encoder SW Pin

#define ROTARYMAX 10
#define ROTARYMIN 0
#define ROTARYSTEPS 1

RotaryEncoder encoder(PIN_IN1, PIN_IN2, RotaryEncoder::LatchMode::TWO03);

int menu = 0;
int currentMenu = 0;

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
  static int pos = 0;
  encoder.tick();
  
  debouncer.update();
  if(debouncer.fell()){
    encoder.setPosition((long)0);
    Serial.print("Push!");
    Serial.print(" pos:");
    Serial.print(pos);
    
    if(menu >10) currentMenu = 0;
    else     currentMenu = menu;
    menu = 1;
    Serial.print(", currentMenu:");
    Serial.print(currentMenu);
    Serial.print(", menu:");
    Serial.println(menu);

  }
    
  int newPos = encoder.getPosition();  
  if (pos != newPos) {
    Serial.print("Trun!");
    Serial.print("pos:");
    Serial.print(newPos);
    pos = newPos;
      
    if((int)encoder.getDirection()==1)
      menu = menu + 1;
    else
      menu = menu - 1;
    Serial.print(", menu:");
    Serial.println(menu);
  }
}
