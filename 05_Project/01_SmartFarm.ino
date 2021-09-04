#include<DHT.h>
#include<Wire.h>
#include<BH1750.h>
#include<LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
BH1750 LightSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);


int fan_control = 8;
int led_control = 9;
int pump_control = 10;

float set_temp, set_hum;
int set_light, set_soil;

void setup(void){
  lcd.begin(16,2);
  lcd.init();
  lcd.clear();
  lcd.backlight();
  dht.begin();

  Wire.begin();
  LightSensor.begin();

  pinMode(pump_control, OUTPUT);
  pinMode(fan_control, OUTPUT);
  pinMode(led_control, OUTPUT);
}

void loop(void){
  int soil_moisture = analogRead(A0);
  mois = 100 - map(soil_moisture, 0,1023, 0,100);

  uint16_t lux = LightSensor.readLightLevel();

  hum = dht.readHumidity();
  temp = dht.readTemperature();

  pump();
  fan_heat();
  sun(lux);

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temp, 1);
  lcd.print("*c");
  lcd.print(" ");
  
  lcd.setCursor(0,1);
  lcd.print("Light:");
  lcd.print(lux);
  lcd.print(" lx");
  lcd.print(" ");
}

void pump(void){
  if(mois>50){
    digitalWrite(pump_control, LOW);
  }else{
    digitalWrite(pump_control, HIGH);
  }
}

void fan_heat(void){
  if(temp>30){
    digitalWrite(fan_control, LOW);
  }else{
    digitalWrite(fan_control, HIGH);
  }
}

void sun(uint16_t lux){
  if(lux<100){
    digitalWrite(led_control, LOW);
  }else{
    digitalWrite(led_control, HIGH);
  }
  delay(2000);
}
