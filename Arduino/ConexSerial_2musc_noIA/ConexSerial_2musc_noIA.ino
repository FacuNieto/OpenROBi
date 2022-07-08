
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


void moverMotorDobleValorCustom( int valor, int motor1, int motor2, int bajo, int alto )
{
  ////////////ingresa valor analogico, lo mapea segun alto y bajo (umbrales)//////////////
  ////////////luego envía a motores dobles////////////////////////////////////////////////
  
  int pulse_wide, ancho_pulso1, ancho_pulso2, potVal;
  pulse_wide = map(valor, bajo, alto, 250, 2300);
  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  pwm.setPWM(motor1, 0, ancho_pulso1);
  pwm.setPWM(motor2, 0, ancho_pulso2);
  // delay (10);
  Serial.println("asdf1");

}

void moverDedosValorCustom( int valor, int bajo, int alto )
{
  //Mueve los flexores proximales, 
  int pulse_wide, ancho_pulso1, ancho_pulso2;
  pulse_wide = map(valor, bajo, alto, 250, 2300);
  ancho_pulso1 = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  ancho_pulso2 = map (ancho_pulso1, 150 , 500 , 500, 150);
  pwm.setPWM(0, 1, ancho_pulso1);//meñique metacarpofalangica
  pwm.setPWM(1, 1, ancho_pulso1);//anular metacarpofalangica
  pwm.setPWM(2, 1, ancho_pulso1);//medio metacarpofalangica
  pwm.setPWM(3, 1, ancho_pulso2);//indice metacarpofalangica
  pwm.setPWM(4, 1, ancho_pulso2);//pulg carpometacarpo flex
  pwm.setPWM(5, 1, ancho_pulso2);//pulg carpometacarpo abdu
  pwm.setPWM(6, 1, map (ancho_pulso1, 150 , 500 , 500, 150));//pulg carpometacarpo abdu
  Serial.println("asdf2");

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
  Serial.setTimeout(0.1);
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
    moverMotorDobleValorCustom( c1, 1, 2, 100, 200 );
    moverDedosValorCustom( c2,100, 200 );
//    Serial.print(c1);
//    Serial.println(c2);


  }

}
