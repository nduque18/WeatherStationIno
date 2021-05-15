#include "DHT.h"
#include <Wire.h>
#include <BMP180.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BMP180 myBMP(BMP180_ULTRAHIGHRES);

int photoR = A0;

unsigned long startTime = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("DHT11 Test"));

  dht.begin();

    while (myBMP.begin() != true)
  {
    Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
    delay(5000);
  }
  
  Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free

  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long actualTime = millis();
  if (actualTime - startTime >= 10000){
    float humidity = dht.readHumidity();
    float temperatureDHT = dht.readTemperature();

    float pressureBMP = myBMP.getPressure();
    float temperatureBMP = myBMP.getTemperature();
    float seaLevelPressureBMP = myBMP.getSeaLevelPressure(2630);

    float lightValue = analogRead(photoR);

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%   Temperature DHT11: ");
    Serial.print(temperatureDHT);
    Serial.println("°C ");
 

    Serial.print("Pressure : ");
    Serial.print(pressureBMP);
    Serial.print("Pa   Temperature BMP180: ");
    Serial.print(temperatureBMP);
    Serial.print("°C   Sea level pressure: ");
    Serial.print(seaLevelPressureBMP);
    Serial.println(" Pa ");

    Serial.println("Illumination: ");
    Serial.print(lightValue/1023*100);
    Serial.println(" % ");
    Serial.println();
    

    startTime = actualTime;
  }
  

}
