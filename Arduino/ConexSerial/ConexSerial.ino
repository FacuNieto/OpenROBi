// Copyright 2022 Facundo Nieto

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Este código permite corroborar la conexión serial entre Python y Arduino. Particularmente se envían 2 valores separados por ",", luego se separan
// y se controlan 2 servomotores con cada valor correspondientemente mapeado.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <SPI.h>
//////////Servos/////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 
#define SERVOMAX  580 
#define USMIN  600 
#define USMAX  2400 
#define FREQUENCY  50
//////////Servos/////////

//////////Filtro/////////
#define alpha 0.05   //Alpha
int ValorfiltradoX1 = 350;
int ValorfiltradoX2 = 350;
//////////Filtro/////////

//////////Inicialización de variables/////////
String serialData;
String xval;
String yval;
int pin = 13;
int c1 = 0;
int c2 = 2;
//////////Inicialización de variables/////////


//////////Funciones/////////

void moverMotor( int ejeacelerometro, int motor)
{
  int pulse_wide, pulse_width;
  
  pulse_wide = map(ejeacelerometro, 0, 100, 600, 2400);//acele
  pulse_width = int (float(pulse_wide ) / 1000000 * FREQUENCY * 4096);
  pwm.setPWM(motor, 0, pulse_width);
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
//////////Funciones/////////


void setup () {
  //Inicializar controlador de servos
  pwm.begin();
  pwm.setPWMFreq(50); //Se define frecuencia de trabajo

  //Inicializar comunicación Serial 
  Serial.begin(500000); //Se trabaja a 500000 baudios
 
  while (!Serial) {
    //se espera la inicialización completa
  }
  Serial.setTimeout(1);//seteo de timeout
}


void loop () {

  if (Serial.available() > 0) {
    
    // Lectura de datos en puerto
    serialData = Serial.readString();
    
    // Split de string por ","
    xval = getValue(serialData, ',', 0);
    yval = getValue(serialData, ',', 1);
    c1 = xval.toInt();
    c2 = yval.toInt();
    
    // Filtrado y mapeo 
    ValorfiltradoX1 = (alpha * c1) + ((1 - alpha) * ValorfiltradoX1);
    ValorfiltradoX2 = (alpha * c2) + ((1 - alpha) * ValorfiltradoX2);
    ValorfiltradoX1 = map(ValorfiltradoX1, 5800 , 7500, 150 , 565);
    ValorfiltradoX2 = map (ValorfiltradoX2, 150 , 565 , 565, 150);
    
    // Seteo de servomotores
    pwm.setPWM(0, 0, ValorfiltradoX1);
    pwm.setPWM(1, 0, ValorfiltradoX2);
    
    // Print de datos por puerto serie
    Serial.print(ValorfiltradoX1);
    Serial.println(ValorfiltradoX2);

  }

}
