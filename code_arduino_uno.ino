#include <OneWire.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27); 
int flag = 0;
int sensor = 0; 
int motor1 = 4;
int motor2 = 12;
int water_level_1 = 1;
int water_level_2 = 2;


OneWire oneWire(2);
void setup()
{
  int error;
  lcd.begin(16,2);
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);
  if (error == 0) {
    Serial.println(": LCD found.");

  } else {
    Serial.println(": LCD not found.");
}

  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(water_level_1, INPUT);
  pinMode(water_level_2, INPUT);

  pinMode(sensor, INPUT);
  lcd.print("Water Irrigaton");
  lcd.setCursor(4,1);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Welcomes You");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
 } 
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

void loop(){
  lcd.setCursor(0,0);
   lcd.setBacklight(255);
    lcd.print("Automatic Mode    ");
    int soil = analogRead(sensor);
    int w1 = analogRead(water_level_1);
    int w2 = analogRead(water_level_2);
    Serial.println(analogRead(sensor));
    Serial.println(analogRead(water_level_1));
    Serial.println(analogRead(water_level_2));
    root["a1"] = soil;
    root["a2"] = w1;
    root["a3"] = w2;
    root.printTo(Serial);

    
if(analogRead(water_level_1)>analogRead(water_level_2))
  {
    if(analogRead(sensor)>=500 && flag==0)
    {
      delay(1000);
      if(analogRead(sensor)>=500)
      {
        lcd.begin(16,2);
        lcd.setCursor(0,1);
        lcd.print("Motor ON    ");
        Serial.println("Motor ON    ");
        digitalWrite(motor1, HIGH);
        delay(2000);
        flag=1;
      }
    }

    else if(analogRead(sensor)<=500 && flag==1)
    {
      delay(1000);
      if(analogRead(sensor)<=500)
      {
        digitalWrite(motor1, LOW);
        lcd.begin(16,2);
        lcd.print("Motor OFF");
        Serial.println("Motor OFF    ");
        lcd.setCursor(0,1);
        lcd.print("Motor OFF");
        delay(2000);
        flag=0;
      }
    }
  }
else if(analogRead(water_level_1)<analogRead(water_level_2))
  {
     if(analogRead(sensor)>=500 && flag==0)
    {
      delay(1000);
      if(analogRead(sensor)>=500)
      {
        lcd.begin(16,2);
        lcd.setCursor(0,1);
        lcd.print("Motor ON    ");
        Serial.println("Motor ON    ");
        digitalWrite(motor2, HIGH);
        delay(2000);
        flag=1;
      }
    }

    else if(analogRead(sensor)<=500 && flag==1)
    {
      delay(1000);
      if(analogRead(sensor)<=500)
      {
        digitalWrite(motor2, LOW);
        lcd.begin(16,2);
        lcd.print("Motor OFF");
        Serial.println("Motor OFF    ");
        lcd.setCursor(0,1);
        lcd.print("Motor OFF");
        delay(2000);
        flag=0;
      }
    }
  }
}
