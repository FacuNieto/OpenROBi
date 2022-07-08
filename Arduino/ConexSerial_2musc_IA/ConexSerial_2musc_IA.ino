
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
  
  if (valor==0){Serial.println("0");}
  if (valor==90){Serial.println("90");}
  if (valor==135){Serial.println("135");}   
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
  Serial.begin(500000);
  pwm.setPWMFreq(50);
  
  while (!Serial) {
  }
  Serial.setTimeout(1);
}

int c1 = 0;

void loop () {

  if (Serial.available() > 0) {
    serialData = Serial.readString();
    c1 = serialData.toInt();
    if (c1==0){moverMotorDobleValorCustom( 0, 1, 2, 0, 135 );}
    if (c1==1){moverMotorDobleValorCustom( 90, 1, 2, 0, 135 );}
    if (c1==2){moverMotorDobleValorCustom( 135, 1, 2,  0, 135 );}           

//    Serial.print(c1);
//    Serial.println(c2);


  }

}
