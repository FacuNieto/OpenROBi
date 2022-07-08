
//#include <SPI.h>
//////////Servos/////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 //175 this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  580 //575 this is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define FREQUENCY  50
//////////Servos/////////

//////////Filtro/////////
#define alpha 0.05   //Alpha
int ValorfiltradoX1 = 350;
int ValorfiltradoX2 = 350;
//////////Filtro/////////

String serialData;
int pin = 13;


void moverMotor( int ejeacelerometro, int motor)
{
  int pulse_wide, pulse_width;

  // lector de valores del potenciometro


  //conversor
  //pulse_wide = map(potVal, 0, 1048, 250, 3000);
  pulse_wide = map(ejeacelerometro, 0, 100, 600, 2400);//acele
  //pulse_wide = map(ejeacelerometro, -32768, 32768, 100, 2300);//gyro
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motor, 0, pulse_width);
  //  Serial.println(ejeacelerometro);
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void setup () {
  pwm.begin();

  //  pinMode(pin, OUTPUT);
  Serial.begin(500000);
  pwm.setPWMFreq(50);
  while (!Serial) {
  }
  Serial.setTimeout(1);
}

int c1 = 0;
int c2 = 2;
int c3 = 3;
String xval;
String yval;

void loop () {

  if (Serial.available() > 0) {
    serialData = Serial.readString();
    xval = getValue(serialData, ',', 0);
    yval = getValue(serialData, ',', 1);
    c1 = xval.toInt();
    c2 = yval.toInt();
    ValorfiltradoX1 = map(c1, 5800 , 7500, 150 , 565);
    ValorfiltradoX2 = map (ValorfiltradoX1, 150 , 565 , 565, 150);
    pwm.setPWM(0, 0, ValorfiltradoX1);
    pwm.setPWM(1, 0, ValorfiltradoX2);
    Serial.print(c1);
    Serial.println(c2);


  }

}
